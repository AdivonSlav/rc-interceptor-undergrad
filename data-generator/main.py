import pandas as pd
import numpy as np

NUM_SAMPLES = 100000
PWM_MIN = 1000
PWM_MAX = 2000

# Function to generate legitimate user data
def generate_legitimate_data(num_samples):
    print("Generating fake legitimate user flight data...")
    time_index = np.linspace(0, 10, num_samples)
    data = {
        'throttle': PWM_MIN + (PWM_MAX - PWM_MIN) * (0.4 + 0.1 * np.sin(time_index)),  # Controlled throttle
        'yaw': PWM_MIN + (PWM_MAX - PWM_MIN) * (0.5 + 0.1 * np.cos(time_index)),      # Gentle yaw
        'pitch': PWM_MIN + (PWM_MAX - PWM_MIN) * (0.45 + 0.1 * np.sin(0.5 * time_index)),  # Moderate pitch
        'roll': PWM_MIN + (PWM_MAX - PWM_MIN) * (0.45 + 0.1 * np.cos(0.5 * time_index))   # Gentle roll
    }
    return pd.DataFrame(data).astype(int)

# Function to generate illegitimate user data
def generate_illegitimate_data(num_samples):
    print("Generating fake illegitimate user flight data...")
    time_index = np.linspace(0, 10, num_samples)
    data = {
        'throttle': PWM_MIN + (PWM_MAX - PWM_MIN) * np.random.uniform(0.3, 1.0, num_samples),  # Erratic throttle
        'yaw': PWM_MIN + (PWM_MAX - PWM_MIN) * np.random.uniform(0.2, 0.8, num_samples),      # Sharp yaw changes
        'pitch': PWM_MIN + (PWM_MAX - PWM_MIN) * np.random.uniform(0.2, 0.8, num_samples),    # Extreme pitch
        'roll': PWM_MIN + (PWM_MAX - PWM_MIN) * np.random.uniform(0.2, 0.8, num_samples)      # High amplitude roll
    }
    return pd.DataFrame(data).astype(int)

def main():
  # Generate data
  legitimate_data = generate_legitimate_data(NUM_SAMPLES)
  illegitimate_data = generate_illegitimate_data(NUM_SAMPLES)

  # Label data
  legitimate_data['legitimate'] = 1
  illegitimate_data['legitimate'] = 0

  combined_data = pd.concat([legitimate_data, illegitimate_data])
  combined_data.to_csv('drone_flight_data.csv', index=False)
  print("Finished writing to CSV")


if __name__ == "__main__":
    main()