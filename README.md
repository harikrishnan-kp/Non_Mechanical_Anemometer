# Non_Mechanical_Anemometer
Currently we’re monitoring weather station parameter such as wind speed and direction using mechanically moving sensors such as cup anemometer and wind vane, problem with such sensors is that they are easy to damage then they are deployed locally.The aim of this project is to find a solution for smart weather station with no mechanical moving parts for measuring all weather conditions with a focus on rain and wind based on low power ML at the edge that can be deployed locally with low cost, low power, reliable, accurate, easy to install and maintain.
# List of Parameters recorded
Wind Velocity and Wind Direction
- Duration measurement
# Prerequisites
- Arduino IDE [Tested]
- Edge Impulse Software [Tested]
- Jupyter Notebook [Tested]
- Google Colab [Tested]
# Sensor
- Transducers salvaged from HCSR04
# Getting started
- Connect the sensor to a microcontroller (Arduino)
- Upload the Data Collection Module script to Arduino  board.
- Once the data collection Completed,Preprocess the data with required timestamp and labels.
- Import the data into Edge Impulse software and Jupyter Notebook
- Data Training
- Impulse Designing
- Model Training
- Performance Evaluation
- Deployment on board Edge module
# Outline
The project divided into 2 phases.
- First phase 

Consider 2 HCSR04 sensor. Transducer salvaged from HCSR04.The transducer modules were found to be marked as R & T respectively by the manufacturers. In this experiment, 2 HCSR04 modules and DHT were used. the transducers are elongated and connected to a 3D printed enclosure orthogonal to each other. Take the time duration between transmitter and receiver. Also temperature and humidity measurements. Because the wind velocity can be calculated using time of flight principle.The time-of-flight principle is based on measuring the time it takes for a wave to travel from a source (a time-of-flight sensor) to an object and back.
Speed of sound depends on temperature and humidity.
Speed of Sound (m/s) = 331.5 + 0.6 * Temperature (°C) + 0.0124 * Humidity (%)
it depends on the temperature , humidity. 
We take a large amount of dataset at different speed levels using pedestrial fan  and move the distance between the non mechanical anemometer setup and the fan. Also compared the wind speed of non mechancial anemometer with digital anemometer.

<img src="https://github.com/shruthigirija/Non_Mechanical_Anemometer/blob/b58546d2d8578afcda4140f39cb8fb23eb196609/Images/Digital_anemometer_with_ultrasonic.jpg" width="500" height="400">

