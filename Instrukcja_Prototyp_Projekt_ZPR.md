# PROTOTYP PROJEKTU KÓŁKO I KRZYŻYK NA STERYDACH - ZPR

## OPIS

W ramach prototypu zostały stworzone ramy finalnego projektu, oraz przetestowane zostały 
główne funkcjonalności, które zostaną rozwinięte i połączone w całość w ramach finalnej wersji projektu.
Udało nam się na ten moment zaimplementować wstępnego klienta, podstawowe funkcjonalności gry w kółko i krzyżyk (bez walidacji ruchów),
Obiekty występujące w grze, wstępny silnik gry. Skupiliśmy się na tym, żeby w ramach prototypu zaprezentować najważniejszy
element projektu, czyli komunikację między klientem, a serwerem. 
Skrypt "build_linux" uruchamia serwer, który można wykorzystać do komunikacji z klientem. 
Skrypt "build_test_main_linux" demonstruje w konsoli pliki JSON wykorzystywane przy komunikacji.
W celu podejrzenia struktury jsona można skorzystać ze strony http://jsonformatter.curiousconcept.com/.
Można również podejrzeć przykładowe wygenerowane jsony w katalogu "templates" wewnątrz katalogu "server"

## STRUKTURA PROJEKTU

Nasz projekt dzieli się na dwa główne podprojekty - klient i serwer. Klient został napisany przy pomocy Angulara
(język TypeScript), a serwer w C++. Istnieje również przykładowa dokumentacja wygenerowana przy pomocy Natural Docs,
która jest na bieżąco powiększana. Istnieje również garść testów jednostkowych stworzony w Catch2. 
Pokrycie testami będzie zdecydowanie większe na końcowym etapie projektu, ponieważ obecnie stworzone struktury nie posiadają jeszcze
obsługi wyjątków i przypadków szczególnych (edge cases). Nie stosowaliśmy też Test Driven Development i skupialiśmy się 
na dostarczeniu jak największej ilości funkcji. 

## INSTRUKCJA

Częsciowe instrukcje w języku angielskim znajdują się również w plikach Readme.md danych podprojektów.
Do uruchomienia skryptów klienta i serwera wymagany jest cmake.

#### Serwer

Należy uruchomić skrypt build_linux.sh na linuksie lub build_win32.ps1 na windowsie.
Otrzymamy wtedy informację o starcie klienta. W obecnym stanie serwer wysyła tylko informację o planszy do klienta.

W ramach testów można zmienić wartości zmiennych outerBoardCoords i innerBoardCoords w pliku HttpHandler.cpp,
żeby umieścić symbol w innym polu.

#### Klient

Należy przejść do katalogu client.
Należy użyć komendy npm install, żeby zainstalować odpowiednie moduły wymagane do działania klienta.
Następnie wystarczy wpisać komendę npm start w celu uruchomienia klienta. 


#### Komunikacja klient-serwer

Wymaga uruchomionego jednocześnie serwera i klienta. W pliku config ustawiony jeest port na którym ma nadawać serwer.
Obecnie klient i serwer są nastawione na adres 1337. Zmiana tej wartości wymaga jednoczesnej zmiany w kliencie. 
W kliencie znajdują się 2 testowe przyciski, które wysyłają zapytania do serwera. W trakcie testów na windowsie trafił nam się błąd,
w którym otrzymaliśmy błąd 426, który wynikał z blokady CORS mimo, że umieszczamy nagłówek w odpowiedziach od serwera. Nie udało nam się obecnie wykryć przyczyny.
Kliknięcie w aplikacji klienta przycisku start game pozwoli podejrzeć w logach json opisujący planszę gry  
jsona planszy w konsoli. Kliknięcie przycisku Reset odświeża stan planszy jednocześnie wykonując zapytanie do serwera o stan planszy,
w efekcie ruch zadany po stronie serwera zostaje umieszczony w kliencie.

#### Testy

należy zainstalować Catch2 i uruchomić skrypt znajdujący się w katalogu server o nazwie "run_tests_catch.sh"

#### Dokumentacja

wystarczy uruchomić plik html index.html znajdujący się w katalogu "docs" przynależącym do projektu.



