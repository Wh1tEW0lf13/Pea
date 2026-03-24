Jeżeli chcemy wczytać dane z pliku, uruchamiamy program następująco `./plik.exe --file <ścieżka_do_pliku> <algorytm> <permutacje>`

Jeżeli chcemy stworzyć nowy losowy graf, uruchamiamy program następująco `./plik.exe --random <size> <algorytm> <permutacje>`

Jeżeli chcemy uruchomić algorytm na ostatniej macierzy, uruchamiamy program następująco `./plik.exe --last <algorytm> <permutacje>`

Jeżeli chcemy wyświetlić ostatnią macierz, uruchamiamy program następująco `./plik.exe --showLast`

Wartości dla <algorytm>:

0 = Brute_Force

1 = Nearest_Neighbour

2 = RelativeNearestNeighbour

3 = Random

Jeżeli nie wybierzemy algorytmu nr. 3, wtedy nie wpisujemy <permutacje> do pliku startowego. Kończymy na `<algorytm>`
