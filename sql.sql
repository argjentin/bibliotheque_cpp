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

-- roman 5 insert values
insert into livres (type, titre, auteur, annee, disponible, personne_nom, personne_prenom, date_emprunt, date_retour) values ('roman', 'Le petit prince', 'Antoine de Saint-Exupéry', 1943, 1, NULL, NULL, NULL, NULL);
insert into livres (type, titre, auteur, annee, disponible, personne_nom, personne_prenom, date_emprunt, date_retour) values ('roman', 'Le seigneur des anneaux', 'J.R.R. Tolkien', 1954, 1, NULL, NULL, NULL, NULL);
insert into livres (type, titre, auteur, annee, disponible, personne_nom, personne_prenom, date_emprunt, date_retour) values ('roman', 'Le rouge et le noir', 'Stendhal', 1830, 1, NULL, NULL, NULL, NULL);
-- dvd 5 insert values
insert into livres (type, titre, auteur, annee, disponible, personne_nom, personne_prenom, date_emprunt, date_retour) values ('dvd', 'Le seigneur des anneaux', 'Peter Jackson', 2001, 1, NULL, NULL, NULL, NULL);
insert into livres (type, titre, auteur, annee, disponible, personne_nom, personne_prenom, date_emprunt, date_retour) values ('dvd', 'Le seigneur des anneaux', 'Peter Jackson', 2002, 1, NULL, NULL, NULL, NULL);
-- magazine 5 insert values
insert into livres (type, titre, auteur, annee, disponible, personne_nom, personne_prenom, date_emprunt, date_retour) values ('magazine', 'Le monde', ' ', 2018, 1, NULL, NULL, NULL, NULL);
insert into livres (type, titre, auteur, annee, disponible, personne_nom, personne_prenom, date_emprunt, date_retour) values ('magazine', 'Le monde', ' ', 2018, 1, NULL, NULL, NULL, NULL);
-- bd 5 insert values
-- insert into livres (type, titre, auteur, annee, disponible, personne_nom, personne_prenom, date_emprunt, date_retour) values ('bd', 'Astérix', 'René Goscinny', 1959, 1, NULL, NULL, NULL, NULL);
insert into livres (type, titre, auteur, annee, disponible, personne_nom, personne_prenom, date_emprunt, date_retour) values ('bd', 'Astérix', 'René Goscinny', 1959, 1, NULL, NULL, NULL, NULL);
