import tkinter as tk
from tkinter import messagebox

# Global variables
appliances = []

# Function to clear dynamic frame
def clear_dynamic_frame(frame):
    for widget in frame.winfo_children():
        widget.destroy()

# Function to show home inputs
def show_home_inputs(dynamic_frame, appliances):
    clear_dynamic_frame(dynamic_frame)

    # Add appliance inputs
    tk.Label(dynamic_frame, text="Add Appliance Details (Name, Power, Usage):", font=("Arial", 12)).pack(anchor="w", pady=5)

    appliance_name = tk.Entry(dynamic_frame)
    appliance_name.pack(fill="x", padx=5, pady=5)
    appliance_power = tk.Entry(dynamic_frame)
    appliance_power.pack(fill="x", padx=5, pady=5)
    appliance_usage = tk.Entry(dynamic_frame)
    appliance_usage.pack(fill="x", padx=5, pady=5)

    def add_appliance():
        name = appliance_name.get()
        try:
            power = float(appliance_power.get())
            usage = float(appliance_usage.get())
            appliances.append({"name": name, "power": power, "hours": usage})
            messagebox.showinfo("Success", f"Added appliance: {name}")
            appliance_name.delete(0, tk.END)
            appliance_power.delete(0, tk.END)
            appliance_usage.delete(0, tk.END)
        except ValueError:
            messagebox.showerror("Error", "Please enter valid power and usage values.")

    tk.Button(dynamic_frame, text="Add Appliance", command=add_appliance).pack(pady=5)

# Function to show tubewell inputs
def show_tubewell_inputs(dynamic_frame, tubewell_kw):
    clear_dynamic_frame(dynamic_frame)
    tk.Label(dynamic_frame, text="Enter Tubewell Power Requirement (in kW):", font=("Arial", 12)).pack(anchor="w", pady=5)
    tk.Entry(dynamic_frame, textvariable=tubewell_kw).pack(fill="x", padx=5, pady=5)

# Function to calculate the system
def calculate_system(system_type, sunlight_hours, budget, tubewell_kw, appliances):
    stype = system_type.get()
    sunlight = sunlight_hours.get()
    user_budget = budget.get()

    if sunlight <= 0:
        messagebox.showerror("Error", "Please enter valid sunlight hours.")
        return

    if user_budget <= 0:
        messagebox.showerror("Error", "Please enter a valid budget.")
        return

    if stype == "home":
        if not appliances:
            messagebox.showerror("Error", "Please add at least one appliance.")
            return
        total_energy = sum(a["power"] * a["hours"] / 1000 for a in appliances)
    elif stype == "tubewell":
        tubewell = tubewell_kw.get()
        if tubewell <= 0:
            messagebox.showerror("Error", "Please enter a valid tubewell power requirement.")
            return
        total_energy = tubewell * sunlight
    else:
        messagebox.showerror("Error", "Please select a system type.")
        return

    system_size = total_energy / sunlight
    inverter_type = recommend_inverter(system_size)
    cost = estimate_cost(system_size)

    # Display results
    display_results(stype, total_energy, system_size, inverter_type, cost)

# Function to recommend inverter type
def recommend_inverter(system_size):
    if system_size <= 5:
        return "Micro-inverter"
    elif 5 < system_size <= 15:
        return "String inverter"
    else:
        return "Hybrid inverter"

# Function to estimate cost
def estimate_cost(system_size):
    panel_cost_per_kw = 46000
    inverter_cost_factor = 50000
    installation_cost_factor = 0.12

    panel_cost = system_size * panel_cost_per_kw
    inverter_cost = inverter_cost_factor + (system_size * 50)
    installation_cost = panel_cost * installation_cost_factor
    total_cost = panel_cost + inverter_cost + installation_cost

    return {
        "Panel Cost": round(panel_cost, 2),
        "Inverter Cost": round(inverter_cost, 2),
        "Installation Cost": round(installation_cost, 2),
        "Total Cost": round(total_cost, 2),
    }

# Function to display results
def display_results(stype, total_energy, system_size, inverter_type, cost):
    result_text = f"System Type: {stype.capitalize()}\n"
    result_text += f"Total Energy Requirement: {total_energy:.2f} kWh\n"
    result_text += f"Recommended System Size: {system_size:.2f} kW\n"
    result_text += f"Recommended Inverter Type: {inverter_type}\n"
    result_text += "\nCost Estimate:\n"
    for key, value in cost.items():
        result_text += f"{key}: {value}\n"

    messagebox.showinfo("System Estimate", result_text)

# Main function to create GUI
def main():
    global appliances
    root = tk.Tk()
    root.title("Solar System Size Estimator")
    root.geometry("600x600")

    # Tkinter variables (created after root)
    system_type = tk.StringVar()
    sunlight_hours = tk.DoubleVar(value=0.0)
    budget = tk.DoubleVar(value=0.0)
    tubewell_kw = tk.DoubleVar(value=0.0)

    # Title
    tk.Label(root, text="Solar System Size Estimator", font=("Arial", 16, "bold")).pack(pady=10)

    # System Type Selection
    frame_type = tk.LabelFrame(root, text="Step 1: Select System Type", padx=10, pady=10)
    frame_type.pack(fill="x", padx=10, pady=5)
    tk.Radiobutton(frame_type, text="Home Installation", variable=system_type, value="home", command=lambda: show_home_inputs(dynamic_frame, appliances)).pack(anchor="w")
    tk.Radiobutton(frame_type, text="Agricultural Tubewell", variable=system_type, value="tubewell", command=lambda: show_tubewell_inputs(dynamic_frame, tubewell_kw)).pack(anchor="w")

    # Sunlight and Budget Inputs
    frame_sunlight = tk.LabelFrame(root, text="Step 2: Sunlight and Budget", padx=10, pady=10)
    frame_sunlight.pack(fill="x", padx=10, pady=5)
    tk.Label(frame_sunlight, text="Average Sunlight Hours per Day:").pack(anchor="w")
    tk.Entry(frame_sunlight, textvariable=sunlight_hours).pack(fill="x", padx=5, pady=5)
    tk.Label(frame_sunlight, text="Budget (in your currency):").pack(anchor="w")
    tk.Entry(frame_sunlight, textvariable=budget).pack(fill="x", padx=5, pady=5)

    # Dynamic Frame for Additional Inputs
    dynamic_frame = tk.LabelFrame(root, text="Step 3: Additional Inputs", padx=10, pady=10)
    dynamic_frame.pack(fill="both", padx=10, pady=5)

    # Calculate Button
    tk.Button(root, text="Calculate System", command=lambda: calculate_system(system_type, sunlight_hours, budget, tubewell_kw, appliances)).pack(pady=10)

    root.mainloop()

# Run the program
if __name__ == "__main__":
    main()
