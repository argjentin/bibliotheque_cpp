DROP TABLE IF EXISTS livres;

CREATE TABLE livres (
    id INT NOT NULL AUTO_INCREMENT,
    type VARCHAR(50) NOT NULL,
    titre VARCHAR(50) NOT NULL,
    auteur VARCHAR(50) NOT NULL,
    annee INT NOT NULL,
    disponible INT NOT NULL,
    personne_nom VARCHAR(50),
    personne_prenom VARCHAR(50),  
    date_emprunt DATE,
    date_retour DATE,
    PRIMARY KEY (id)
);

insert into livres (type, titre, auteur, annee, disponible) values ('roman', 'Le petit prince', 'Antoine de Saint-Exupéry', 1943, 1);
insert into livres (type, titre, auteur, annee, disponible) values ('roman', 'Le seigneur des anneaux', 'J.R.R. Tolkien', 1954, 1);
insert into livres (type, titre, auteur, annee, disponible) values ('roman', 'Le Hobbit', 'J.R.R. Tolkien', 1937, 1);

insert into livres (type, titre, auteur, annee, disponible) values ('bd', 'Asterix', 'René Goscinny', 1959, 1);
insert into livres (type, titre, auteur, annee, disponible) values ('bd', 'Lucky Luke', 'Morris', 1946, 1);
insert into livres (type, titre, auteur, annee, disponible) values ('bd', 'Astérix chez les Bretons', 'René Goscinny', 1968, 1);
insert into livres (type, titre, auteur, annee, disponible) values ('bd', 'Astérix et la Transitalique', 'René Goscinny', 1971, 1);

insert into livres (type, titre, auteur, annee, disponible) values ('dvd', 'Scarface', 'Brian De Palma', 1983, 1);
insert into livres (type, titre, auteur, annee, disponible) values ('dvd', 'Sin City', 'Frank Miller', 2005, 1);
insert into livres (type, titre, auteur, annee, disponible) values ('dvd', 'Zombieland', 'Ruben Fleischer', 2009, 1);
insert into livres (type, titre, auteur, annee, disponible) values ('dvd', 'The Dark Knight', 'Christopher Nolan', 2008, 1);

insert into livres (type, titre, auteur, annee, disponible) values ('magazine', 'Lire', 'Lire', 1990, 1);
insert into livres (type, titre, auteur, annee, disponible) values ('magazine', 'Paris Match', 'Paris Match', 1949, 1);
insert into livres (type, titre, auteur, annee, disponible) values ('magazine', 'Le Point', 'Le Point', 1973, 1);
insert into livres (type, titre, auteur, annee, disponible) values ('magazine', 'Le Monde', 'Le Monde', 1944, 1);