import tkinter as tk
from tkinter import ttk, messagebox
import ttkbootstrap as tb

class SolarEstimator:
    def __init__(self):
        self.appliances = []
        self.root = tb.Window(themename="cosmo")
        self.root.title("Solar System Estimator")
        self.root.geometry("700x800")
        
        # Recommendations data
        self.RECOMMENDED_INVERTERS = {
            "Micro-inverter": ["Huawei", "Growatt", "Fronius"],
            "String inverter": ["Sungrow", "GoodWe", "SolarMax"],
            "Hybrid inverter": ["Tesla", "Hybrid Solar Solutions", "Alpha ESS"],
        }
        self.RECOMMENDED_SOLAR_PANELS = [
            "Jinko Solar", "Canadian Solar", "JA Solar", 
            "Trina Solar", "LONGi Solar"
        ]
        
        # Style configuration
        self.style = tb.Style()
        self.style.configure("Title.TLabel", font=("Helvetica", 24, "bold"))
        self.style.configure("Subtitle.TLabel", font=("Helvetica", 12))
        
        self.create_header()
        self.create_main_content()
        
    def create_header(self):
        header = tb.Frame(self.root, bootstyle="primary")
        header.pack(fill="x", pady=(0, 20))
        
        title = tb.Label(
            header,
            text="Solar System Estimator",
            font=("Helvetica", 24, "bold"),
            foreground="white",
            bootstyle="inverse-primary"
        )
        title.pack(pady=20)
        
        subtitle = tb.Label(
            header,
            text="Calculate your solar power requirements",
            font=("Helvetica", 12),
            foreground="white",
            bootstyle="inverse-primary"
        )
        subtitle.pack(pady=(0, 20))

    def create_main_content(self):
        main_frame = tb.Frame(self.root)
        main_frame.pack(fill="both", expand=True, padx=30, pady=20)
        
        # System Type Selection
        type_frame = tb.Labelframe(
            main_frame,
            text="Step 1: Select System Type",
            padding=15,
            bootstyle="primary"
        )
        type_frame.pack(fill="x", pady=(0, 15))
        
        self.system_type = tk.StringVar(value="home")
        tb.Radiobutton(
            type_frame,
            text="Home Installation",
            variable=self.system_type,
            value="home",
            command=self.show_home_inputs,
            bootstyle="primary"
        ).pack(pady=5)
        
        tb.Radiobutton(
            type_frame,
            text="Agricultural Tubewell",
            variable=self.system_type,
            value="tubewell",
            command=self.show_tubewell_inputs,
            bootstyle="primary"
        ).pack(pady=5)
        
        # Sunlight Hours Input
        self.sunlight_hours = tk.DoubleVar(value=0.0)
        sun_frame = tb.Labelframe(
            main_frame,
            text="Step 2: Sunlight Hours",
            padding=15,
            bootstyle="primary"
        )
        sun_frame.pack(fill="x", pady=(0, 15))
        
        tb.Entry(
            sun_frame,
            textvariable=self.sunlight_hours,
            bootstyle="primary"
        ).pack(fill="x", pady=5)
        
        # Dynamic Content Frame
        self.dynamic_frame = tb.Labelframe(
            main_frame,
            text="Step 3: System Details",
            padding=15,
            bootstyle="primary"
        )
        self.dynamic_frame.pack(fill="both", expand=True, pady=(0, 15))
        
        # Calculate Button
        tb.Button(
            main_frame,
            text="Calculate System",
            command=self.calculate,
            bootstyle="success",
            width=20
        ).pack(pady=20)
        
        self.tubewell_kw = tk.DoubleVar(value=0.0)
        self.show_home_inputs()

    def show_home_inputs(self):
        self.clear_dynamic_frame()
        
        # Appliance input fields
        tb.Label(
            self.dynamic_frame,
            text="Appliance Name:",
            bootstyle="primary"
        ).pack(anchor="w")
        name_entry = tb.Entry(self.dynamic_frame, bootstyle="primary")
        name_entry.pack(fill="x", pady=(0, 10))
        
        tb.Label(
            self.dynamic_frame,
            text="Power (Watts):",
            bootstyle="primary"
        ).pack(anchor="w")
        power_entry = tb.Entry(self.dynamic_frame, bootstyle="primary")
        power_entry.pack(fill="x", pady=(0, 10))
        
        tb.Label(
            self.dynamic_frame,
            text="Usage (Hours/Day):",
            bootstyle="primary"
        ).pack(anchor="w")
        usage_entry = tb.Entry(self.dynamic_frame, bootstyle="primary")
        usage_entry.pack(fill="x", pady=(0, 10))
        
        def add_appliance():
            try:
                self.appliances.append({
                    "name": name_entry.get(),
                    "power": float(power_entry.get()),
                    "hours": float(usage_entry.get())
                })
                for entry in [name_entry, power_entry, usage_entry]:
                    entry.delete(0, tk.END)
                messagebox.showinfo("Success", "Appliance added successfully!")
            except ValueError:
                messagebox.showerror("Error", "Please enter valid numbers")
        
        tb.Button(
            self.dynamic_frame,
            text="Add Appliance",
            command=add_appliance,
            bootstyle="info"
        ).pack(pady=10)

    def show_tubewell_inputs(self):
        self.clear_dynamic_frame()
        tb.Label(
            self.dynamic_frame,
            text="Tubewell Power (kW):",
            bootstyle="primary"
        ).pack(anchor="w")
        tb.Entry(
            self.dynamic_frame,
            textvariable=self.tubewell_kw,
            bootstyle="primary"
        ).pack(fill="x", pady=5)

    def clear_dynamic_frame(self):
        for widget in self.dynamic_frame.winfo_children():
            widget.destroy()

    def recommend_inverter(self, system_size):
        if system_size <= 5:
            return "Micro-inverter"
        elif 5 < system_size <= 15:
            return "String inverter"
        else:
            return "Hybrid inverter"

    def calculate(self):
        sunlight = self.sunlight_hours.get()
        if sunlight <= 0:
            messagebox.showerror("Error", "Please enter valid sunlight hours")
            return

        if self.system_type.get() == "home":
            if not self.appliances:
                messagebox.showerror("Error", "Please add at least one appliance")
                return
            total_energy = sum(a["power"] * a["hours"] / 1000 for a in self.appliances)
        else:
            tubewell = self.tubewell_kw.get()
            if tubewell <= 0:
                messagebox.showerror("Error", "Please enter valid tubewell power")
                return
            total_energy = tubewell * sunlight

        system_size = total_energy / sunlight
        inverter_type = self.recommend_inverter(system_size)
        cost = self.estimate_cost(system_size)
        
        # Create enhanced results window
        result = tb.Toplevel(self.root)
        result.title("System Estimate")
        result.geometry("600x700")
        
        # Header
        header = tb.Frame(result, bootstyle="primary")
        header.pack(fill="x")
        tb.Label(
            header,
            text="Solar System Recommendation",
            font=("Helvetica", 20, "bold"),
            foreground="white",
            bootstyle="inverse-primary"
        ).pack(pady=20)

        # Main content
        content = tb.Frame(result)
        content.pack(fill="both", expand=True, padx=30, pady=20)

        # System Details Section
        details_frame = tb.Labelframe(
            content,
            text="System Details",
            padding=15,
            bootstyle="primary"
        )
        details_frame.pack(fill="x", pady=(0, 15))

        system_details = f"""
System Type: {self.system_type.get().capitalize()}
Required System Size: {system_size:.2f} kW
Daily Energy Requirement: {total_energy:.2f} kWh
Recommended Inverter Type: {inverter_type}
"""
        tb.Label(
            details_frame,
            text=system_details,
            justify="left",
            wraplength=500
        ).pack(anchor="w")

        # Cost Breakdown Section
        cost_frame = tb.Labelframe(
            content,
            text="Cost Breakdown",
            padding=15,
            bootstyle="primary"
        )
        cost_frame.pack(fill="x", pady=(0, 15))

        for item, value in cost.items():
            tb.Label(
                cost_frame,
                text=f"{item}: Rs. {value:,.2f}",
                font=("Helvetica", 10),
                bootstyle="primary"
            ).pack(anchor="w", pady=2)

        # Recommendations Section
        rec_frame = tb.Labelframe(
            content,
            text="Recommended Equipment",
            padding=15,
            bootstyle="primary"
        )
        rec_frame.pack(fill="x", pady=(0, 15))

        # Inverter recommendations
        tb.Label(
            rec_frame,
            text=f"Recommended {inverter_type} Companies:",
            font=("Helvetica", 10, "bold")
        ).pack(anchor="w", pady=(0, 5))
        
        for company in self.RECOMMENDED_INVERTERS[inverter_type]:
            tb.Label(
                rec_frame,
                text=f"• {company}",
                bootstyle="primary"
            ).pack(anchor="w")

        # Solar panel recommendations
        tb.Label(
            rec_frame,
            text="Recommended Solar Panel Brands:",
            font=("Helvetica", 10, "bold")
        ).pack(anchor="w", pady=(10, 5))
        
        for panel in self.RECOMMENDED_SOLAR_PANELS:
            tb.Label(
                rec_frame,
                text=f"• {panel}",
                bootstyle="primary"
            ).pack(anchor="w")

        # Close button
        tb.Button(
            content,
            text="Close",
            command=result.destroy,
            bootstyle="secondary"
        ).pack(pady=10)

    def estimate_cost(self, system_size):
        panel_cost = system_size * 46000
        inverter_cost = 50000 + (system_size * 50)
        installation_cost = panel_cost * 0.12
        total_cost = panel_cost + inverter_cost + installation_cost
        
        return {
            "Panel Cost": panel_cost,
            "Inverter Cost": inverter_cost,
            "Installation Cost": installation_cost,
            "Total Cost": total_cost
        }

    def run(self):
        self.root.mainloop()

if __name__ == "__main__":
    app = SolarEstimator()
    app.run()