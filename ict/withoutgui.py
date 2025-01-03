import tkinter as tk
from tkinter import ttk, messagebox
import ttkbootstrap as tb

class SolarEstimator:
    def __init__(self):
        self.appliances = []
        self.root = tb.Window(themename="cosmo")
        self.root.title("Solar System Estimator")
        self.root.geometry("700x800")
        
        # Style configuration
        self.style = tb.Style()
        self.style.configure("Title.TLabel", font=("Helvetica", 24, "bold"))
        self.style.configure("Subtitle.TLabel", font=("Helvetica", 12))
        
        self.create_header()
        self.create_main_content()
        
    def create_header(self):
        # Create gradient-like header
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
        # Main content container with padding
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

    def calculate(self):
        # Calculation logic remains the same as your original code
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

        # Display results in a modern message box
        system_size = total_energy / sunlight
        cost = self.estimate_cost(system_size)
        
        result = tb.Toplevel(self.root)
        result.title("System Estimate")
        result.geometry("500x400")
        
        tb.Label(
            result,
            text="System Estimate",
            font=("Helvetica", 18, "bold"),
            bootstyle="primary"
        ).pack(pady=20)
        
        text = tb.Text(result, height=15, width=50)
        text.pack(padx=20, pady=10)
        text.insert("1.0", f"""
System Size: {system_size:.2f} kW
Daily Energy: {total_energy:.2f} kWh

Cost Breakdown:
• Panel Cost: Rs. {cost['Panel Cost']:,.2f}
• Inverter Cost: Rs. {cost['Inverter Cost']:,.2f}
• Installation: Rs. {cost['Installation Cost']:,.2f}
• Total Cost: Rs. {cost['Total Cost']:,.2f}
""")
        text.configure(state="disabled")

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