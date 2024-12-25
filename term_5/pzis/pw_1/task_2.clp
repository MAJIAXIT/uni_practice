; Helper Functions: Member Check and Question Asking
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

; Rule 1: Do you prefer a common or exotic pet?
(defrule ask-pet-type
   =>
   (bind ?response (ask-question "Do you prefer a common (1) or exotic (2) pet?" 1 2))
   (if (eq ?response 1)
       then (assert (preference common))
       else (assert (preference exotic))))

; Rule 2: For common pets - Indoor or outdoor lifestyle?
(defrule ask-common-lifestyle
   (preference common)
   =>
   (bind ?response (ask-question "Do you prefer an indoor (1) or outdoor (2) pet?" 1 2))
   (if (eq ?response 1)
       then (assert (lifestyle indoor))
       else (assert (lifestyle outdoor))))

; Rule 3: For exotic pets - Low or high maintenance?
(defrule ask-exotic-maintenance
   (preference exotic)
   =>
   (bind ?response (ask-question "Do you prefer a low-maintenance (1) or high-maintenance (2) pet?" 1 2))
   (if (eq ?response 1)
       then (assert (maintenance low))
       else (assert (maintenance high))))

; Rule 4: Suggest indoor common pets
(defrule suggest-indoor-common-pet
   (preference common)
   (lifestyle indoor)
   =>
   (bind ?response (ask-question "Do you want a cuddly (1) or independent (2) pet?" 1 2))
   (if (eq ?response 1)
       then (assert (pet cat))
       else (assert (pet fish))))

; Rule 5: Suggest outdoor common pets
(defrule suggest-outdoor-common-pet
   (preference common)
   (lifestyle outdoor)
   =>
   (bind ?response (ask-question "Do you want a guard pet (1) or a friendly pet (2)?" 1 2))
   (if (eq ?response 1)
       then (assert (pet dog))
       else (assert (pet rabbit))))

; Rule 6: Suggest low-maintenance exotic pets
(defrule suggest-low-maintenance-exotic-pet
   (preference exotic)
   (maintenance low)
   =>
   (bind ?response (ask-question "Do you want a pet that is easy to observe (1) or requires interaction (2)?" 1 2))
   (if (eq ?response 1)
       then (assert (pet reptile))
       else (assert (pet hamster))))

; Rule 7: Suggest high-maintenance exotic pets
(defrule suggest-high-maintenance-exotic-pet
   (preference exotic)
   (maintenance high)
   =>
   (bind ?response (ask-question "Do you want a pet with a unique look (1) or one that mimics humans (2)?" 1 2))
   (if (eq ?response 1)
       then (assert (pet parrot))
       else (assert (pet monkey))))

; Rule to Print the Recommended Pet
(defrule print-pet-recommendation
   (pet ?type)
   =>
   (printout t crlf "Your recommended pet is: " ?type crlf)
   (halt))
