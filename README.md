# telefonskiImenik

Elektronsko vodenje evidenc telefinskih številk. Uporabljeni oprimki.

primer vnosa:
$ ./baza -o 4 4<>spo.dat -tel 022207000 -ime Janez -priimek Novak -dan 23 -mesec 1 -leto 1985

primer iskanja po imenu in priimku:
$ ./baza -o 3 3<>spo.dat -ime Janez -priimek Novak

primer iskanja po priimku:
$ ./baza -o 3 3<>spo.dat -priimek Novak

kreiranje baze:
$ ./baza -c
