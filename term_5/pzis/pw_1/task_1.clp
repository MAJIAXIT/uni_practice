(deffunction member (?item $?list)
   (if (or (not ?list) (eq ?item (nth$ 1 ?list)))
       then TRUE
       else (member ?item (rest$ ?list))))

(deffunction ask-question (?question $?allowed-values)
   (printout t ?question " ")
   (bind ?answer (read))
   (if (lexemep ?answer) 
       then (bind ?answer (lowcase ?answer)))
   (while (not (member ?answer ?allowed-values)) do
       (printout t ?question " ")
       (bind ?answer (read))
       (if (lexemep ?answer) 
           then (bind ?answer (lowcase ?answer))))
   ?answer)

;; Rule 1: First or second course?
(defrule determine-course
   =>
   (bind ?response (ask-question "Is the dish a first course (1) or second course (2)?" 1 2))
   (if (eq ?response 1)
       then (assert (course first-course))
       else (assert (course second-course))))

;; Rule for First Course
(defrule determine-first-course
   (course first-course)
   =>
   (bind ?response (ask-question "Is the dish fish-based (1), meat-based (2), or vegetable-based (3)?" 1 2 3))
   (if (eq ?response 1)
       then (assert (dish ukha-soup))
       else 
       (if (eq ?response 2)
           then (assert (dish kharcho-soup))
           else (assert (dish beetroot-soup)))))

;; Rule 3: Beef or chicken?
(defrule determine-meat-type
   (course second-course)
   =>
   (bind ?response (ask-question "Is the dish made from beef (1) or chicken (2)?" 1 2))
   (if (eq ?response 1)
       then (assert (meat beef))
       else (assert (meat chicken))))

;; Rule 4: Sliced or chunks of beef?
(defrule determine-beef-form
   (meat beef)
   =>
   (bind ?response (ask-question "Is the beef sliced (1) or in chunks (2)?" 1 2))
   (if (eq ?response 1)
       then (assert (dish azu))
       else (assert (dish entrecote))))

;; Rule 5: Minced or pieces of chicken?
(defrule determine-chicken-form
   (meat chicken)
   =>
   (bind ?response (ask-question "Is the chicken minced (1) or in pieces (2)?" 1 2))
   (if (eq ?response 1)
       then (assert (dish pozharsky-cutlets))
       else (assert (dish chakhokhbili))))

;; Print the result
(defrule print-dish
   (dish ?item)
   =>
   (printout t crlf "Suggested dish: " ?item crlf))
