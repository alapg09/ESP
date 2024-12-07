# Core logic for solar system calculation 

def add_appliances():
    """
    Collects appliance data from the user via console input.
    Returns a list of appliances with their power and usage details.
    """
    appliances = []
    while True:
        print("\nEnter details for an appliance:")
        name = input("Appliance Name (or type 'done' to finish): ")
        if name.lower() == 'done':
            break
        try:
            power = float(input("Power (in Watts): "))
            hours = float(input("Usage per day (in Hours): "))
            appliances.append({"name": name, "power": power, "hours": hours})
            print(f"Added appliance: {name}")
        except ValueError:
            print("Invalid input! Power and usage must be numeric.")
    return appliances


def calculate_home_energy(appliances):
    """
    Calculates the total daily energy requirement for home appliances in kWh.
    """
    return sum(a["power"] * a["hours"] / 1000 for a in appliances)


def calculate_tubewell_energy(tubewell_power_kw, sunlight_hours):
    """
    Calculates the total daily energy requirement for a tubewell in kWh.
    """
    return tubewell_power_kw * sunlight_hours


def recommend_inverter(system_size):
    """
    Recommends an inverter type based on the system size in kW.
    """
    if system_size <= 5:
        return "Micro-inverter"
    elif 5 < system_size <= 15:
        return "String inverter"
    else:
        return "Hybrid inverter"


def estimate_cost(system_size):
    """
    Estimates the cost of a solar system based on its size in kW.
    Costs are tailored to the Pakistani market.
    """
    # Costs in PKR
    panel_cost_per_kw = 100000  # PKR per kW
    inverter_base_cost = 50000  # Base inverter cost in PKR
    inverter_cost_factor = 2000  # Additional inverter cost per kW
    installation_cost_factor = 0.12  # Installation cost as 12% of panel cost

    # Calculate costs
    panel_cost = system_size * panel_cost_per_kw
    inverter_cost = inverter_base_cost + (system_size * inverter_cost_factor)
    installation_cost = panel_cost * installation_cost_factor
    total_cost = panel_cost + inverter_cost + installation_cost

    return {
        "Panel Cost": round(panel_cost, 2),
        "Inverter Cost": round(inverter_cost, 2),
        "Installation Cost": round(installation_cost, 2),
        "Total Cost": round(total_cost, 2),
    }


def calculate_system(system_type, sunlight_hours, budget, appliances=None, tubewell_power_kw=None):
    """
    Main function to calculate the system requirements.
    Takes:
    - system_type: "home" or "tubewell"
    - sunlight_hours: Average sunlight hours per day
    - budget: Available budget in PKR
    - appliances: List of appliances (only for home)
    - tubewell_power_kw: Tubewell power in kW (only for tubewell)
    Returns a dictionary with the results.
    """
    if sunlight_hours <= 0:
        raise ValueError("Sunlight hours must be greater than 0.")
    if budget <= 0:
        raise ValueError("Budget must be greater than 0.")

    # Calculate energy requirement
    if system_type == "home":
        if not appliances:
            raise ValueError("Appliances list is empty.")
        total_energy = calculate_home_energy(appliances)
    elif system_type == "tubewell":
        if not tubewell_power_kw or tubewell_power_kw <= 0:
            raise ValueError("Tubewell power must be a positive number.")
        total_energy = calculate_tubewell_energy(tubewell_power_kw, sunlight_hours)
    else:
        raise ValueError("Invalid system type. Choose 'home' or 'tubewell'.")

    # Calculate system size
    system_size = total_energy / sunlight_hours
    inverter_type = recommend_inverter(system_size)
    cost = estimate_cost(system_size)

    # Return results
    return {
        "System Type": system_type,
        "Total Energy Requirement": round(total_energy, 2),
        "Recommended System Size": round(system_size, 2),
        "Recommended Inverter Type": inverter_type,
        "Cost Estimate": cost,
    }


# Temporary console interface (will be replaced with GUI in later stages)
def main():
    print("Solar System Estimator")
    print("1. Home Installation")
    print("2. Agricultural Tubewell")
    system_type = input("Select the system type (1 or 2): ")

    try:
        sunlight_hours = float(input("Enter average sunlight hours per day: "))
        budget = float(input("Enter your budget in PKR: "))
    except ValueError:
        print("Error: Invalid input for sunlight hours or budget.")
        return

    if system_type == "1":
        # Home installation
        appliances = add_appliances()
        if not appliances:
            print("Error: No appliances were added.")
            return
        result = calculate_system("home", sunlight_hours, budget, appliances=appliances)
    elif system_type == "2":
        # Tubewell
        try:
            tubewell_power_kw = float(input("Enter tubewell power requirement (in kW): "))
        except ValueError:
            print("Error: Invalid input for tubewell power.")
            return
        result = calculate_system("tubewell", sunlight_hours, budget, tubewell_power_kw=tubewell_power_kw)
    else:
        print("Error: Invalid system type selection.")
        return

    # Display results
    print("\nSystem Estimate:")
    print(f"System Type: {'Home' if result['System Type'] == 'home' else 'Tubewell'}")
    print(f"Total Energy Requirement: {result['Total Energy Requirement']} kWh")
    print(f"Recommended System Size: {result['Recommended System Size']} kW")
    print(f"Recommended Inverter Type: {result['Recommended Inverter Type']}")
    print("\nCost Estimate (in PKR):")
    for key, value in result["Cost Estimate"].items():
        print(f"{key}: {value}")


if __name__ == "__main__":
    main()
