# Algorytm-Szeregowania-Zadan

 Poniżej umieszczam fragmenty dokumentacji.
 Projekt zarealizowany w ramach zajęć na uczelni.

#1 . Wstęp

Poniższa dokumentacja stanowi wprowadzenie i opis projektu-programu: „Opracowanie algorytmu szeregowania zadań, Algorytm 5.4”. 
Algorytm 5.4 jest wzorcem wyznaczającym uszeregowanie optymalne na podstawie znajomości rozwiązania problemu programowania liniowego
– wzór został opisany w książce J. Błażewicza „Badania operacyjne dla Informatyków”[1]. 
Znajduje się w rozdziale 5.2 „Minimalizacja długości uszeregowania”.  

Program został napisany w języku C++. 
Wykorzystano przy tym środowisko programistyczne Qt Creator 3.5 przy użyciu biblioteki Qt 5.5.


#3 . Opis programu

Program został napisany w języku programowania C++, przy wykorzystaniu
techniki programowania obiektowego. Składa się on z następujących klas:
  
  ▪ Okno
  
  ▪ OknoDodawania
  
  ▪ Silnik
  
  ▪ Wykres
  
  ▪ Napis
  
  ▪ Macierz
  
  ▪ Zdarzenie
  
Klasa „Okno” jest główną klasą programu. Zawiera deklaracje dotyczące graficznego
interfejsu głównego okna aplikacji, wyniki działań na macierzach i zbiorach takie jak:
macierze T, Y, V, zbiór φ , długość σ, czas C max zbiór danych wejściowych przechowujący
listę zadań, liczbę wykorzystywanych procesorów, zbiór zdarzeń wyjściowych
reprezentujący wynik oraz obiekty innych klas takich jak OknoDodawania, Wykres,
Napis, Macierz.
Klasa „OknoDodawania” jest nieskomplikowanym oknem służącym do dodawania
Zadań przez użytkownika. Kolejne zdarzenia tworzą zbiór które następnie są kopiowane
do zbioru wejściowego znajdującego się w klasie Okno.
Klasa „Silnik” zarządza pracą obiektu Okno. On odpowiada za prawidłowe zakończenie
pracy jak i rozpoczęcie. Zawiera również metodę odpowiedzialną za utworzenie okna
powitalnego.
Klasa „Zdarzenie” reprezentuje pojedyncze zadanie dodawane przez użytkownika a
następnie przetwarzane przez program. Zawiera informacje takie jak nazwa – jego
format to Z%%, gdzie %% to nazwa zadania (liczba nazw jest ograniczona do
jedenastu, czyli od Z0 do Z10, gdzie Z0 jest przestojem procesora), czas potrzebny na
wykonanie przez procesor, numer procesora oraz przesunięcie – pole to związane jest z
informacją potrzebną do narysowania w oknie. Przedstawia ona wartość w jednostkach
czasu i „mówi” ile czasu jest zajętego przez inne zadania dla konkretnego procesora.
Klasy „Wykres”, „Napis”, „Macierz” są obiektami graficznym które odpowiadają za
rysowanie w głównym oknie bieżących informacji o: macierzach T, Y, V, zbiorze φ ,
długości σ, czasie C max, i zadaniach v max , v min 
