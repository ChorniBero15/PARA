# Compress (20 ქულა)

თქვენი ამოცანაა იმპლემენტაცია გაუკეთოთ Compress ფუნქციას, რომელმაც კომპრესირება უნდა გაუკეთოს მოცემულ რიცხვების მიმდევრობას.

* მიმდევრობის თითოეული რიცხვი შედგება ზუსტად 4 **ბიტისგან** ანუ არის 0-დან 15-ის ჩათვლით
* შესაბამისად ერთ ბაიტში ინახება ორი რიცხვი, მაგალითად `0b01011101` ბაიტი აღწერს შემდეგ ორ რიცხვს 5 (`0101` - მარცხნიდან პირველი ოთხი ბიტი) და 13 (`1101` - ბოლო ოთხი ბიტი). `0bxxxx` ნოტაცია C-ში საშუალებას გაძლევთ რიცხვი ორობითში დაწეროთ.
* მოცემული რიცხვების რაოდენობა წინასწარ არ იცით, რიცხვების მიმდევრობა ბოლოვდება 4 ბიტიანი ნული რიცხვით. მაგალითად [`0b01011101`, `0b11110000`] შეიცავს სამ 4 ბიტიან რიცხს, ხოლო [`0b01011101`, `0b11110111`, `0b00000000`] შეიცავს ოთხ რიცხვს.

სრული მაგალითები:

* რიცხვების მიმდევრობა [1, 2, 3, 4] მეხსიერებაში წერია როგორც [`0b00010010`, `0b00110100`, `0b00000000`]
* რიცხვების მიმდევრობა [1, 2, 3, 4, 5] მეხსიერებაში წერია როგორც [`0b00010010`, `0b00110100`, `0b01010000`]

კომპრესირების შედეგად მიმდევრობით მდგომი ერთი და იგივე მნიშვნელობის რიცხვები ნაცვლდება წყვილით: რამდენჯერ მეორდება რიცხვი და გამეორებული რიცხვის მნიშვნელობა. **გარანტირებულია რომ ერთი და იგივე რიცხვი მიყოლებით 15-ზე მეტჯერ არ გვხვდება.** შესაბამისად რიცხვის გამეორების რაოდენობა და რიცხვის მნიშვნელობა შეიძლება 8 ბიტში (1 ბაიტში) ჩაიწეროს, სადაც პირველი ოთხი ბიტი აღნიშნავს განმეორების რაოდენობას, ხოლო მომდევნო ოთხი აღნიშნავს რიცხვის მნიშვნელობას.

მაგალითად თუ გვაქვს რიცხვების შემდეგი მიმდევრობა: [`0b00010001`, `0b01010101`, `0b01010000`]

* ეს ნიშნავს რომ ჯამში გვაქვს 5 რიცხვი [1, 1, 5, 5, 5]. პირველი ორი 4 ბიტიანი რიცხვია `0001`, მომდევნო სამი არის `0101`, ხოლო შემდეგ მოდის `0000` ანუ მიმდევრობის დაბოლოება.
* შესაბამისად ერთიანი მეორდება ორჯერ, ხოლო ხუთიანი - სამჯერ, ანუ ვიღებთ შემდეგი განმეორების წყვილებს: <2;1>, <3;5>
* <2;1> ერთ ბაიტში ჩაიწერება როგორც `0b00100001`
* <3;5> ერთ ბაიტში ჩაიწერება როგორც `0b00110101`
* შესაბამისად საწყისი რიცხვების მიმდევრობის კომპრესირებული ვერსიის შესანახად საჭიროა ორი ბაიტი.


კიდევ ერთი მაგალითი:
* [1, 1, 5, 5, 5, 1] ---> [<2;1>, <3;5>, <1;1>]
* [1, 1, 5, 5, 5, 1] ---> [<2-ჯერ;1-იანი>, <3-ჯერ;5-იანი>, <1-ხელ;1-იანი>]

ამ შემთხვევაში data და out მეხსიერებაში უნდა გამოიყურებოდეს ასე:
* [`0b00010001`, `0b01010101`, `0b01010001`, `0b00000000`] ---> [`0b00100001`, `0b00110101`, `0b00010001`]



**int Compress(void\* data, void\* out)**:

* **data** მიმთითებელზე ჩაწერილია ბიტიანი რიცხვების მიმდევრობა
* უკან უნდა დააბრუნოთ თუ რამდენი ბაიტია საჭირო მიმდევრობის კომპრესირებული ვერსიის შესანახად
* ხოლო კომპრესირების შედეგი უნდა ჩაწეროთ **out** მისამართზე, სადაც უკვე წინასწარ გამოყოფილია საკმარისი მეხსიერება

გარანტირებულია, რომ:

* გადმოცემული void\* მისამართი არანულოვანია.

## ტესტირება

ნაშრომის დასაკომპილირებლად ტერმინალში გაუშვით: `gcc *.c` ხოლო ტესტებზე შესამოწმებლად: `a.exe`
