; 1
(define (first-elem lst)
    (if (null? lst) "None"
        (car lst))
)

; 2
(define (abs_ x)
    (if (negative? x) (* x -1) 
        x)
)

; 3
(define (right-triangle lst)
    (if (= (+ (* (car lst) (car lst)) (* (cadr lst) (cadr lst))) (* (caddr lst) (caddr lst))) #t
        #f)
)

; 4
(define (last-elem lst)
    (cond ((null? lst) "None")
          ((null? (cdr lst)) (car lst))
          (else (last-elem (cdr lst))))
)

; 5
(define (length_ lst)
    (if (null? lst) 0 
        (+ 1 (length_ (cdr lst))))
)

; 6
(define (k-th-element lst k)
    (cond ((null? lst) "None") 
          ((= k 0) (car lst))
          (else (k-th-element (cdr lst) (- k 1)))
    )
)

; 7
(define (filter-range lst a b)
    (cond ((null? lst) '())
          ((or (and (<= (car lst) a) (>= (car lst) b)) (and (<= (car lst) b) (>= (car lst) a)))  
          (cons (car lst) (filter-range (cdr lst) a b)))
          (else (filter-range (cdr lst) a b))
    )
)

(define (prime_helper n k)
    (cond ((= n k) #t)
          ((zero? (modulo n k)) #f)
          (else (prime_helper n (+ k 1)))
    )
)

; 8
(define (prime? n)
    (cond ((= n 1) #f)
          (else (prime_helper n 2))
    )
)

; 9 - next seminar
(define (primes? lst)
    (cond ((null? lst) '())
          ((prime? (car lst)) (cons #t (primes? (cdr lst))))
          (else (cons #f (primes? (cdr lst))))
    )
)
