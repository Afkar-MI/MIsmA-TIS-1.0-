# MIsmA-TIS-1.0-

The **MIsmA TIS 1.0** is a sophisticated control board designed to manage two Transmissive Reconfigurable Intelligent Surfaces (RIS) simultaneously. Each RIS comprises 100-unit cells, requiring precise and independent control.

<img src="/Printed Board/PCB.jpg" width="533" height="400">

## System Architecture

### 1. Microcontroller Unit (MCU)
- **Model**: `TMS320F28379D`
- The MCU processes an 82-byte data packet received from an external source, typically a computer. It generates the control clock signals for the shift register, enabling each row of the D-Latch array one by one and synchronizing output data for each row. The MCU coordinates the timing and sequencing of data storage and retrieval across the system.

### 2. Shift Register & D-Latch Circuit Array
- The system is organized into `16 rows and 40 columns` of D-Latch circuits, forming 1600 total latches. 
- Each row's D-Latches are enabled by a shift register, while each column's input pin is connected to the MCU for precise control over the 1600 output signals.
- This setup allows for the efficient management of the 1600 output pins required by the RIS system.

### 3. Power Supply
- The board is powered by `7 single DC power lines`. A linear voltage regulator `(AZ1117I)` converts the 5V input to 3.3V, providing a maximum current of 1.35A per line.

### 4. Data Communication
- The control board receives an **82-byte data packet** (e.g., `4050ABCFF...`) from an external computer. This data packet contains the necessary instructions for configuring the unit cells in the RIS.
- The MCU processes the incoming data and generates clock signals that enable the D-Latch circuits, assigning output data to rows one by one.

### 5. Control Flow
- The MCU sends shift clock signals to the shift register, enabling the D-Latches row by row. While doing so, the MCU sends output data to the relevant row, which is stored in the D-Latches until the next data cycle.

### 6. Development Software
- **PCB Design**: `Altium Designer`
- **Firmware**: `Code Composer Studio`
