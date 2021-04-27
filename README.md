practice code

@enduml

@startuml
 :start;
 fork
   repeat :foo1;
   :foo2;
   repeat while ()
 fork again
    :foo2;
   :foo3;
   detach
 endfork
 if (foo4) then
   :foo5;
   detach
 endif
 :foo6;
 detach
 :foo7;
 stop
@enduml