#modele du sac a dos

#donnees

param M; #capacite du sac

param n; #nombre d'objets

param t{i in 1..n}; #taille du bloc i

param v{i in 1..n}; #valeur du bloc i

#variable xi=1 si bloc i est choisi

var x{1..n} binary;

#objectif

maximize f :sum {i in 1..n} v[i]*x[i];

#contraintes

subject to

capacite : sum{i in 1..n} t[i]*x[i] <= M;

printf "---Debut de la resolution ---\n";

solve;

printf "---Fin de la resolution ---\n";

display x;

end;
