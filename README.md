# Intuitionistic-Logic-Proof-Assistant

A proof assistant for intuitionistic logic
The operators are 
  /\ - AND
  \/ - OR
  -> - IMPLIES
 
With the constant
  False 

Like most forms of intuitionsitic logic, we have ~P := P -> False

To prove a statement compile the C++ files and run the program

To set a goal type "set-goal P" where P is your fully parenthesized statement

The commands are
  intro - introduces assumptions
  exact "H" - where H is a statement in your context, exact "H" will prove your statement if it is structurally identical to the goal
  impElim "H0" "H1" - implication elimination, given P -> Q and P results in Q
  andElim "H" - and elimination, given A /\ B results in A, B
  orElim "H" - or elimination, given A \/ B will create one context with A and another context with B, to prove your goal you must prove it in each case
  botElim "H" - bot elimination, principle of explosion, if False is in your context allows one to solve anything
  impIntro "H0" "H1" - given A, B in context results in A -> B
  andIntro "H0" "H1" - given A, B in context results in A /\ B
  left - if the goal is of the form A \/ B changes the goal to B (a fake version of or introduction)
  right - if the goal is of the form A \/ B changes the goal to A (a fake version of or introduction)
  assert P - P is a proposition, assumes P and adds it to context but then adds P as a subsequent goal
  
  
 TO DO
  - implement parsing for ~P
  - optional axioms for classical logic and intermediate logics
    - First order forall qualifier will allow people to implement their own axioms and use previously proven statements
  - maybe use this as a basis for higher-order logic

  
