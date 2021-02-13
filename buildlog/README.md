
# Byggelogg

## Dag 1

Vi møttest hjå Dag. Erik brukte dagen på å jobbe med sitt digitale sjakkbrett. Dag venta på delar til sin eigen duppedings, og derfor blei han med på mitt prosjekt i dag. Det vi gjorde var:

- Eg satte opp Raspberry Pi med nyflasha operativsystem
- Dag kopla opp [LED-matrisa](https://www.adafruit.com/product/2279), heretter matrisa. Først kopla han opp vekselstraum inn til straumforsyninga, som eg hadde fått låne med Erik. Deretter kopla han opp 5V DC inn til matrisa. Til sist kopla han opp GPIO-pins på RPi til dataporten på matrisa. Det var rundt 14 kablar som skulle til.
- Eg leita etter software til å drive matrisa. Først prøvde vi ein npm-pakke som var ein wrapper rundt [dette biblioteket til C++](https://github.com/hzeller/rpi-rgb-led-matrix), men denne fekk vi ikkje til å fungere. Vi endte opp med å bruke biblioteket direkte i staden.
- Etter mykje prøving og feiling, både med npm-pakken og med C++-biblioteket, fann vi ut at vi hadde kopla feil. Vi fann eit anna koplingsdiagram som viste seg å vere det korrekte. Etter å ha kopla om til dette fekk vi C++-biblioteket til å fungere. 🎉
- C++-biblioteket hadde mange demos vi kunne køyre, og suksessen blei desto større sidan vi kunne vise masse feite greier på matrisa. 🍻

![](./img/d1/IMG_0140_small.jpeg)
![](./img/d1/IMG_0141_small.jpeg)
![](./img/d1/IMG_0143_small.jpeg)
![](./img/d1/IMG_0144_small.jpeg)
![](./img/d1/IMG_0145_small.jpeg)
![](./img/d1/IMG_0146_small.jpeg)
![](./img/d1/IMG_0149_small.gif )
