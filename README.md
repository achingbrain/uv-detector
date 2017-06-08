# UV sensor sketch

An Arduino sketch to show readings from a UV sensor on an LCD shield in mW/cm^2.

## Bill of materials

1. Arduino Uno
1. [LCD1602 LCD display](http://www.ebay.co.uk/itm/162511933623)
1. [ML8511 UV sensor module](http://www.ebay.co.uk/itm/132170914771)

## Connections

Attach LCD shield to Arduino, then connect UV sensor module pins as follows:

| ML8511 | Arduino |
| ------ | ------- |
| VIN    | -       |
| 3V3    | A2      |
| GND    | GND     |
| OUT    | A1      |
| EN     | 3.3V    |

Leave the `VIN` pin unconnected (if present).

## Instructions

1. Install [Platform.io](http://platformio.org/) plugin for [Atom](https://atom.io/)
1. Install [LiquidCrystal](http://platformio.org/lib/show/887/LiquidCrystal) Arduino library
    ```
    platformio lib install 887
    ```
1. Upload sketch and press any button on the shield to cycle between readings
