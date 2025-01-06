(define (digits n) 
    (if (< n 10) (list n)
        (append (digits (quotient n 10))
                (list (modulo n 10)))
    )
)

(define (list_power lst)
  (let ((n (length lst)))
    (map (lambda (num) (expt num n)) lst)))


(define (sum lst)
    (apply + lst)
)

(define (narcisisstic? n)
    (if (= n (sum (list_power (digits n)))) #t
        #f 
    )
)

(define (count n lst)
    (cond 
        ((null? lst) 0)
        ((= n (car lst)) (+ 1 (count n (cdr lst))))
        (else (count n (cdr lst)))
    )
)


(define (set_helper lst lst0)
    (cond
        ((null? lst) lst0)
        ((zero? (count (car lst) lst0)) 
            (set_helper (cdr lst) (cons (car lst) lst0)))
        (else (set_helper (cdr lst) lst0))
    )
) 

(define (set lst) 
    (set_helper lst '())
)

(define (frequency lst)
	(map (lambda (numb) (list numb (count numb lst))) (set lst))
)


(define (multiplyone n k)
	(if (zero? n) '()
		(cons k (multiplyone (- n 1) k))
	)
)

(define (multiply n lst)
    (apply append (map (lambda (numb) (multiplyone n numb)) lst))
)


(define (ksubset n lst)
    (cond 
        ((zero? n) '(()))
        ((null? lst) '())
        (else 
            (append
            (map (lambda (l) (cons (car lst) l)) (ksubset (- n 1) (cdr lst)))
            (ksubset n (cdr lst)))
        )
    )
)



