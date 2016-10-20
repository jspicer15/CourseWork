#lang racket
(require eopl/eopl)

;John Spicer
;I pledge my honor that I have abided by the Stevens Honor System.

;4

(define-datatype dTree dTree?
  (leaf-t
   (n number?))
  (node-t
   (a symbol?)
   (left dTree?)
   (right dTree?)))

;5

(define d1
  (node-t 'w (node-t 'x (leaf-t 2) (leaf-t 5)) (leaf-t 8)))

(define d2
  (node-t 'w (node-t 'x (leaf-t 2) (leaf-t 5)) (node-t 'y (leaf-t 7) (leaf-t 5))))
  

;6
;a
;dTree? -> number?

(define dTree-height
  (lambda (x)
    (cases dTree x
      (leaf-t (n) 0)
      (node-t (a left right)
              (+ 1 (max (dTree-height left) (dTree-height right)))))))
         
;b
;dTree? -> number?

(define dTree-size
  (lambda (x)
    (cases dTree x
      (leaf-t (n) 1)
      (node-t (a left right)
              (+ 1 (dTree-size left) (dTree-size right))))))

;c
;dTree? -> list?

(define dTree-paths
  (lambda (x)
    (helper '() x)))

(define helper
  (lambda (path x)
    (cases dTree x
      (leaf-t (n) (list path))
      (node-t (a left right)
              (append (helper (append path '(0)) left) (helper (append path '(1)) right))))))

;d
;dTree? -> boolean?

(define dTree-perfect?
  (lambda (t)
    (cases dTree t
      (leaf-t (n) #t)
      (node-t (a left right)
              (eq? (dTree-height left) (dTree-height right))))))

;e
;dTree? -> dTree?

(define dTree-map
  (lambda (f g t)
    (cases dTree t
      (leaf-t (n) (leaf-t (g t)))
      (node-t (a left right) (node-t ((f a) left right))
              (dTree-map (f left g))
              (dTree-map (f g right))))))

;number? -> number?

(define succ
  (lambda (x) (+ x 1)))

;symbol? -> symbol?

(define symbol-upcase
   (compose string->symbol (compose string-upcase symbol->string)))







