#Polish Olympiad in Informatics
#Task: Pisarze
#Score: 42/100

import os,re,string,math,sys,readline

class WritersDetector(object):
    def clean(self, s):
        translator = str.maketrans("", "", string.punctuation)
        return s.translate(translator)

    def tokenize(self, text):
        text = self.clean(text).lower()
        return re.split("\W+", text)

    def get_word_counts(self, words):
        word_counts = {}
        for word in words:
            word_counts[word] = word_counts.get(word, 0.0) + 1.0
        return word_counts

    def fit(self, X, Y):
        self.num_messages = {}
        self.log_class_priors = {}
        self.word_counts = {}
        self.vocab = set()

        n = len(X)
        self.num_messages['sienkiewicz'] = sum(1 for label in Y if label == 2)
        self.num_messages['mickiewicz']  = sum(1 for label in Y if label == 1)
        self.num_messages['prus']        = sum(1 for label in Y if label == 0)

        self.log_class_priors['sienkiewicz'] = math.log(self.num_messages['sienkiewicz'] / n)
        self.log_class_priors['mickiewicz']  = math.log(self.num_messages['mickiewicz'] / n)
        self.log_class_priors['prus']        = math.log(self.num_messages['prus'] / n)

        self.word_counts['sienkiewicz'] = {}
        self.word_counts['mickiewicz']  = {}
        self.word_counts['prus']        = {}

        for x, y in zip(X, Y):
            if y == 2:
               c = 'sienkiewicz'
            elif y == 1:
               c = 'mickiewicz'
            else:
               c = 'prus'

            counts = self.get_word_counts(self.tokenize(x))
            for word, count in counts.items():
                if word not in self.vocab:
                    self.vocab.add(word)
                if word not in self.word_counts[c]:
                    self.word_counts[c][word] = 0.0

                self.word_counts[c][word] += count

    def predict(self, x):
            counts = self.get_word_counts(self.tokenize(x))
            sienkiewicz_score = 0
            mickiewicz_score  = 0
            prus_score        = 0
            for word, _ in counts.items():
                if word not in self.vocab: continue

                log_w_given_sienkiewicz = math.log( (self.word_counts['sienkiewicz'].get(word, 0.0) + 1) / (self.num_messages['sienkiewicz'] + len(self.vocab)) )
                log_w_given_mickiewicz  = math.log( (self.word_counts['mickiewicz'].get(word, 0.0) + 1) / (self.num_messages['mickiewicz'] + len(self.vocab)) )
                log_w_given_prus        = math.log( (self.word_counts['prus'].get(word, 0.0) + 1) / (self.num_messages['prus'] + len(self.vocab)) )


                sienkiewicz_score += log_w_given_sienkiewicz
                mickiewicz_score  += log_w_given_mickiewicz
                prus_score        += log_w_given_prus

            sienkiewicz_score += self.log_class_priors['sienkiewicz']
            mickiewicz_score  += self.log_class_priors['mickiewicz']
            prus_score        += self.log_class_priors['prus']

            if sienkiewicz_score >= mickiewicz_score and sienkiewicz_score >= prus_score:
                return "Sienkiewicz"
            elif sienkiewicz_score <= mickiewicz_score and mickiewicz_score >= prus_score:
                return "Mickiewicz"
            else:
                return "Prus"



if __name__ == '__main__':
    NBA = WritersDetector()
    y = [2,1,0]
    X = ["Winicjusz go jego zas jej rzekl by tak ktory Petroniusz mnie ci gdy Lecz sie przez jeszcze juz bylo tylko sobie przy ktora jednak byl nad czym lub wiec panie ktorych lecz przed moze ktore chwili tym poczal Ligia jakby teraz tego byc Na nawet albowiem Ale pod cezara Winicjusza czy cezar Nero mowil Tak ku sam To bedzie ten niz ktorego jest ty jako oczy nim ktorej bo to Chilo jesli iz miedzy Ligii ktorym odpowiedzial byla ludzi ja im aby znow mogl ona tej ni Ligie wiecej je gdzie sa domu Czy bez zarazem wreszcie ta wszystkich ow wsrod tu dlatego Ursus tych Nie Akte gdyby tam wowczas mial wszystko On odrzekl ludzie chwila ani wszystkie coraz glowe tez takze moja cos bowiem Z Oto zycie twarz Ja mi chcial Apostol O Piotr nia Rzym potem Chrystusa czlowiek Petroniusza gdyz chrzescijan spytal ma Chrystus dalej chwile Wiec Tu Panie nic miasta wszyscy raz mu zycia wiesz wiem dzis rece jedna byly glosem chce Wowczas wobec Tymczasem Gdy dotad oni jaka cale nimi niej jeden czas rowniez oto mowic Eunice Ty swa jakie duszy albo zawolal smierci poczely on niewolnikow Jesli cala jakis jakas bardziej nam nagle mysl mozna we swiata sama kto caly wam miasto Ligio glos Co chrzescijanie swiat smierc serce rzeczy razie Pomponia niech milosc lud Za Tygellinus razem poczela nowe Winicjuszowi twoja twarzy nauka inni bogow woli niego moje jestem choc zupelnie tymczasem soba jakies inaczej co rzekla obok musi mimo kolo kilka dobrze wprawdzie widok trzeba mogla innych cie Chilon Cezar Aulus zawsze slowa pomyslal oczyma Nerona moj dom ciebie sposob procz po nocy nastepnie Kto glowa dopiero dlaczego wszystkim rzeklszy Poppea poczeli nas Jego dzien droga tobie kazal jakkolwiek glowy zbyt siebie przeciw przecie milosci mam Jakoz inne imie ich dni Apostola","w sie i z na nie I do ze jak to A za po o juz a tak co W od ja Na Nie byl Z Ze jest nim mu go pan Sedzia Hrabia Ale rzekl Jak Bo gdy tylko mnie Lecz ich pod jako dla tym To tam tu Tadeusz u nad lecz Wojski ten Tak bez jej przy przez Ja przed jeszcze on Gdy bo sam ku bylo O Juz ma domu mi oczy mial jego by wszyscy On te nas gdzie czy Co Czy Az Gerwazy tez znowu Telimena sobie kto rece az we tej szlachta glowy choc wiec Pan Wiec razem raz bedzie ale sa nawet Klucznik glowe ziemi reka jakby dzis Za Tu Robak Po kiedy je bardzo was Tadeusza Podkomorzy potem byla zamku moze albo wszystko Od tego moj miedzy ktory siebie rzecz Rykow reke Do strony niej nich lub krzyknal Jesli cala zawsze niech ni dwa ty Teraz teraz Ten coz zaraz Potem wszystkie szlachty pana Niech nic Litwie gosci dotad coraz Tylko tych Sedziego Jako gory gdyby Asesor Zosia Wtem Rejent glowa drzwi czas Bog Kto Choc wszystkich wielki ta swiecie nam koniec dlugo zas wtenczas stal ktorej ci ani Tymczasem tyle Tam ktora dwoch bron Zosi wie tylu reku okiem nigdy Ktory ksztalt im czlowiek cie chcial wkolo trzeba panow panie mogl mam koncu Jest jesli Horeszkow chce znak wnet swe swa srod serce nikt ktorych ksiadz cos widac przeciez pole pierwszy Ktora Jacek Hrabiego byly zamek wolna swej stary Soplica slowo Panie niby lat glos Ach zeby zawolal Wszystko Wszyscy wielka takze swych srodku soba Rzekl oczyma my Maciej kazdy Gdzie dworze drugiej czym wy Wozny tuz przerwal ow niz niegdys Nawet Moze Major Lub jeden Dzis dwie drzewa dobrze ciebie wielkie Widac usta U Soplicow Sam rak pol", "Wokulski pan sie ja pani mu go mnie Nie juz tylko jej nawet panie Ale panna sobie ktory dla Izabela ten I czy jego jeszcze odparl on azeby bardzo ma albo u przez moze pana byl rubli tysiecy wiec Pan przed bo ktora przy to rzekl Wokulskiego tej Na kiedy Rzecki mowil tym To chwili O czlowiek No tu znowu te zas byc tego co tam pod bylo jednak dzis Co ci Ignacy jezeli ich ani sa mial Tak ktore bedzie gdzie sam Wiec nad Czy Ach tak bez spytal jestem wszystko Ja Coz jest panny ona Izabeli panu baron Z nic gdy myslal nas cos Ochocki mowi Po  Panna miedzy ktorym raz jakby wiecej ktorych zawolal moj chce Wasowska nim mam by pare potem taki Moze ktorej Bo baronowa oczy jakis rzekla Stach tych kilka byla wiem ludzi Niech sposob dalej Pani ktorzy Starski cie im dopiero wie szepnal niej lecz kto ty Tomasz ta Za dwa troche stary lat dodal Stawska odpowiedzial coz kobieta Jak dobrze razy nam Juz teraz niech choc zaczal je gdyby anizeli dzien drugi jeden ktorego ile czlowieka we mozna moja kobiety caly Szlangbaum Stawskiej pomyslal Panie Szuman sklep roku Wokulskiemu nie oni mowie wszyscy musi glosem zawsze wszystkie tez pania niego mruknal mowila drzwi dni prawie Jezeli dom A taka siebie On domu dnia zapytal mysli mi Kiedy Od no Kto Gdy Zreszta moje glowe przecie nagle ludzie glowa Boze tyle Potem ojciec pozniej majatek zawolala rece pieniadze jaki swoja reke pokoju panne ksiaze jakas Do czym coraz wlasnie sklepu Maruszewicz zycie wtracil razie mogl miala jestes ale trzy rzeczy panowie jakie cala prezesowa okolo takie zaraz Prosze odpowiedziala Naturalnie moge jedna chcial swoje interes az swego sama prawda nia chyba chwile zreszta Tymczasem mlody miec doktor bede mysle lepiej Lecki Izabele"]
    NBA.fit(X, y)

    num = int(input())

    while num>0:
      num -= 1
      a = sys.stdin.readline()
      print (NBA.predict(a))
