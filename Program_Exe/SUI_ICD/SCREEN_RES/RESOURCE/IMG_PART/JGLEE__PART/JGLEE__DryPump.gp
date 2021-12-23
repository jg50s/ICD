#BITMAP
{
JGLEE__Pump_On.bmp
0 0 64 64
0
}
#DYNAMIC
{
#CHANNEL dSetCH
#CHANNEL dStsCH
#CHANNEL dOnSts
IF_OR: (dStsCH == dOnSts)
VIS 1
}
#BITMAP
{
JGLEE__Pump_Off.bmp
0 0 64 64
0
}
#DYNAMIC
{
IF_OR: (dStsCH != dOnSts)
VIS 1
}
