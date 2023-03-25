DROP TABLE IF EXISTS livres;

CREATE TABLE livres (
    id INT NOT NULL AUTO_INCREMENT,
    type VARCHAR(50) NOT NULL,
    titre VARCHAR(50) NOT NULL,
    auteur VARCHAR(50) NOT NULL,
    annee INT NOT NULL,
    disponible INT NOT NULL,
    PRIMARY KEY (id)
);

-- roman
INSERT INTO livres (type, titre, auteur, annee, disponible) VALUES ('roman', 'titre1', 'auteur1', 2010, 1);
INSERT INTO livres (type, titre, auteur, annee, disponible) VALUES ('roman', 'titre2', 'auteur2', 2011, 1);
INSERT INTO livres (type, titre, auteur, annee, disponible) VALUES ('roman', 'titre3', 'auteur3', 2012, 1);
-- dvd
INSERT INTO livres (type, titre, auteur, annee, disponible) VALUES ('dvd', 'titre15', 'auteur15', 2015, 1);
INSERT INTO livres (type, titre, auteur, annee, disponible) VALUES ('dvd', 'titre16', 'auteur16', 2016, 1);
-- magazine
INSERT INTO livres (type, titre, auteur, annee, disponible) VALUES ('magazine', 'titre17', 'auteur17', 2017, 1);
INSERT INTO livres (type, titre, auteur, annee, disponible) VALUES ('magazine', 'titre18', 'auteur18', 2018, 1);
-- bd
INSERT INTO livres (type, titre, auteur, annee, disponible) VALUES ('bd', 'titre19', 'auteur19', 2019, 1);
INSERT INTO livres (type, titre, auteur, annee, disponible) VALUES ('bd', 'titre20', 'auteur20', 2020, 1);