# Non_Mechanical_Anemometer
Currently we’re monitoring weather station parameter such as wind speed and direction using mechanically moving sensors such as cup anemometer and wind vane, problem with such sensors is that they are easy to damage then they are deployed locally.The aim of this project is to find a solution for smart weather station with no mechanical moving parts for measuring all weather conditions with a focus on rain and wind based on low power ML at the edge that can be deployed locally with low cost, low power, reliable, accurate, easy to install and maintain.
# List of Parameters recorded
Wind Velocity and Wind Direction
Duration measurement
# Prerequisites
- Arduino IDE [Tested]
- Edge Impulse Software [Tested]
- Jupyter Notebook [Tested]
- Google Colab [Tested]
# Getting Started
- Connect the Components as shown in the Wiring Diagram
- Upload the Data Collection Module script to Arduino BLE Sense board.
- Collect the Data using Arduino Megaboard
- Once the data collection Completed
- Preprocess the data with required timestamp and labels.
- Import the data into Edge Impulse software
- Data Training
- Impulse Designing
- Model Training
- Performance Evaluation
- Deployment on board Edge module
- New hardware developed for data collection
