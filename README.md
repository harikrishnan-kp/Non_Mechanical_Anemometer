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
- Transducers
# Getting started
- Connect the sensor to a microcontroller (Arduino) [circuit diagram](https://github.com/shruthigirija/Non_Mechanical_Anemometer/blob/83b56dc9e4bb26d55bc2e0940b8e8ad90644d819/Hardware/circuit_diagram.png) & [final circuit diagram](https://github.com/shruthigirija/Non_Mechanical_Anemometer/blob/3a38a9814a3b25b9900fe5588a3d1948c85f6072/Hardware/Final_Circuit_Diagram_Ultrasonic_Anemometer.pdf).
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
### First phase 

Consider 2 HCSR04 sensor. Transducer salvaged from HCSR04.The transducer modules were found to be marked as R & T respectively by the manufacturers. In this experiment, 2 HCSR04 modules and DHT were used. The transducers are elongated and connected to a 3D printed enclosure orthogonal to each other. Take the time duration between transmitter and receiver. Also temperature and humidity measurements. Because the wind velocity can be calculated using time of flight principle.The time-of-flight principle is based on measuring the time it takes for a wave to travel from a source (a time-of-flight sensor) to an object and back.
Speed of sound depends on temperature and humidity.

**Speed of Sound (m/s) = 331.5 + 0.6 * Temperature (°C) + 0.0124 * Humidity (%)**

It depends on the temperature , humidity. 
We take a large amount of dataset at different speed levels using pedestrial fan  and move the distance between the non mechanical anemometer setup and the fan. Also compared the wind speed of non mechancial anemometer with digital anemometer.

<img src="https://github.com/shruthigirija/Non_Mechanical_Anemometer/blob/b58546d2d8578afcda4140f39cb8fb23eb196609/Images/Digital_anemometer_with_ultrasonic.jpg" width="500" height="400">

Data collected as csv file [Dataset](https://github.com/shruthigirija/Non_Mechanical_Anemometer/tree/391bb9dc54901b64c6703b10e69fe1d312284d60/Dataset/forward_velocity_data).

Combined the csv file as [data](https://github.com/shruthigirija/Non_Mechanical_Anemometer/blob/352eefff3b7fbba30cfa4295033f3098b924074d/ML_Model_creation/combined_data_direction_velocity(1).csv).

In this the duration 1 and duration 2 are taken from the HCSR04 module and the temperature and humidity value taken from DHT22. These values are compared with the readings from a digital anemometer.Thus the digital anemometer value marked as Velocity.

Direction taken by the experiment 

<img src="https://github.com/shruthigirija/Non_Mechanical_Anemometer/blob/79d4757ce54ac5e38c9678aad24b8e2ec2ae0cf9/Images/Exp_Setup2.jpg" width="500" height="1084">

ML model creation using the dataset [model_creation](https://github.com/shruthigirija/Non_Mechanical_Anemometer/blob/79d4757ce54ac5e38c9678aad24b8e2ec2ae0cf9/ML_Model_creation/combined_data_direction_velocity_ai_algorithm(all).py).

All models and the output shows below

<img src="https://github.com/shruthigirija/Non_Mechanical_Anemometer/blob/2be12674111fa830dbdfe23fcedea64dcd0d3ed0/Images/result.png" width="500" height="400">

### Second Phase

Second phase of the project [anemometer document](https://github.com/shruthigirija/Non_Mechanical_Anemometer/blob/ddd9cc8e9ba9b56fa7ea026a515ed27bcfd959de/Documentation/Development_of_Inhouse_Non_Mechanical_Anemometer__v_1_2_.pdf) attached here.Ultrasonic anemometer is used to measure wind velocity and direction for weather stations and other industrial applications. It consists of ultrasonic transducers, signal processing unit, amplifier, bandpass filter and also a sonic anemometer is used. Transducers are used to generate 40KHz ultrasonic sound waves.Signal routing is used to control the sensor operation and to reduce the hardware complexity by reusing the transmitter and receiver circuit. Amplifier is used to amplify the receiver.The received signal first passes from the amplifier stage to increase the strength of the signal after that it passes through the band pass filter which is having a center frequency of 40 kHz and bandwidth of 10kHz, to remove the unwanted frequency component.Bandpass filter designed for this purpose.
The block diagram of ultrasonic transducer setup.

<img src="https://github.com/shruthigirija/Non_Mechanical_Anemometer/blob/c472eb2cb6dc8963a3f4fcdc3e665c3b5b8d4bac/Images/nm_anemometer_inhouse_block.png" width="500" height="500">

The [Hardware setup](https://github.com/shruthigirija/Non_Mechanical_Anemometer/blob/5aa0c476e579870c4133b7e94617aa4176a62458/Images/hardware_setup.jpg).

The [code](https://github.com/shruthigirija/Non_Mechanical_Anemometer/blob/c861909e140a28759b107ddf321069bbb6cf47ca/Software/Arduino/Ultrasonic_anemometer_final_code.ino) uploaded to the arduino nano ble 33 sense board.
From this we got time duration as Tn-s,Ts-n,Te-w.Tw-e. After the calculation, found the wind velocity and the [result](https://github.com/shruthigirija/Non_Mechanical_Anemometer/blob/837bcef9634a177f138992c08d9da77a130b260d/Images/anemometer_result.png) attached here.

Result takes on the basis of [Indoor](https://github.com/shruthigirija/Non_Mechanical_Anemometer/blob/c861909e140a28759b107ddf321069bbb6cf47ca/Images/anemometer_indoor.jpg)and [outdoor](https://github.com/shruthigirija/Non_Mechanical_Anemometer/blob/adcc814a70aa7188f4c5506e82b20594172a5258/Images/Image%201outdoor%20test%201.jpg) test.

# Enclosure
<img src=https://github.com/shruthigirija/Non_Mechanical_Anemometer/blob/5aa0c476e579870c4133b7e94617aa4176a62458/Images/Anemometer.jpg>



