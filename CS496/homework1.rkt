#lang racket
;I pledge my honor that I have abided by the Stevens Honor System
(define (seven)
  7)

(define (sign n)
	(if (< n 0)
		-1
	(if (> n 0)
		1
	0)))

(define (absolute n)
	(if (< n 0)
		(* n -1)
	n))

(define (andp x y)
	(if (equal? x #t)
		(if (equal? y #t)
			#t
		#f)
	#f))

(define (orp x y)
	(if (equal? x #t)
		#t
	(if (equal? y #t)
		#t
        #f)))

(define (notp x y)
	(if (equal? x y)
#f
#t))

(define (xorp x y)
	(if (equal? x #t)
		(if (equal? y #t)
			#f
		#t)
	(if (equal? x #f)
		(if (equal? y #t)
			#t
                 #f)
         #f)))

(define (dividesBy x y)
	(if (zero? (remainder x y))
		#t
	#f))

(define (singleton? x)
  	(match x
    		['() #f]
   		 [(cons h t) (null? t)]
   		 [_ #f]))

(define (swap x)
  	(match x
  		 [(cons h t) (append (list (car t) h) (cdr t))]
   		 [_ #f]))

(define (app x y)
  (x y))

(define (twice x y)
  (x (x y)))

(define (compose x y z)
  (x (y z)))