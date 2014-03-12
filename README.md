openAutoWater
=============

arduino controlled watering system based on soil moisture levels

Uses soil moisture sensor from DFRobot to measure soil moisture level,
and a relay to give power to the recepticle.
It will turn on a device (i.e. sump, irrigation system) to water when it detects dry conditions.

moisture sensor - vcc to digital02; value to analog0; gnd to gnd
Relay - relayCoil02 to digital03; relayCoil01 to gnd; 120v hot to Relay switch; 120v to nema 5-15R recepticle

Keep It Simple Stupid.
