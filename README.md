First repo, this will be used to track progress on a simple EMG reader using the myoware sensor.

Hardware:
-ESP32 Feather V2
-Myoware Sensor
-Myoware Shield (with 3.5mm connector)
-1 Aux cable (cut and soldered to connections on shield to allow for quick connection

Software Goals:
Short term:
-Reliably report through serial connection (9600 baud) sensor output.
-apply a Kalman filter to find actual EMG results (if needed, envelope numbers are provided)

Long term:
-Plot EMG response for the last 5-10seconds on a featherwing OLED display
-Make a library so that all initialization/plotting/filtering occurs
