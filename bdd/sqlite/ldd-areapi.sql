--- LDD (langage de définition de données)

--- Supprime les tables

DROP TABLE IF EXISTS Score;
DROP TABLE IF EXISTS Partie;
DROP TABLE IF EXISTS Rencontre;
DROP TABLE IF EXISTS Joueur;
DROP TABLE IF EXISTS Club;

--- Table Club

CREATE TABLE IF NOT EXISTS Club(idClub INTEGER PRIMARY KEY AUTOINCREMENT, nomClub VARCHAR);

--- Remarque : il faudrait un concept Equipe à l'intérieur d'un Club
--- Il peut y avoir plusieurs Equipe dans un Club. Un Joueur peut probablement participer à plusieurs Equipe dans un même Club.

--- Table Joueur

CREATE TABLE IF NOT EXISTS Joueur(numeroLicence INTEGER PRIMARY KEY, idClub INTEGER NOT NULL, nom VARCHAR, prenom VARCHAR, CONSTRAINT fk_idClub_1 FOREIGN KEY (idClub) REFERENCES Club(idClub), UNIQUE(nom,prenom));

--- Autres :
--- Catgérorie -> V1/-50, S/-40, J1/-16, etc...
--- Classement/Points -> 17/1745, 11/1129, etc...

--- Table Rencontre

CREATE TABLE IF NOT EXISTS Rencontre(idRencontre INTEGER PRIMARY KEY AUTOINCREMENT, idClubA INTEGER NOT NULL, idClubB INTEGER NOT NULL, nbPartiesGagnantes INTEGER DEFAULT 0, estFinie INTEGER DEFAULT 0, horodatage DATETIME NOT NULL, CONSTRAINT fk_idClub_A FOREIGN KEY (idClubA) REFERENCES Club(idClub), CONSTRAINT fk_idClub_B FOREIGN KEY (idClubB) REFERENCES Club(idClub));

--- Table Partie

CREATE TABLE IF NOT EXISTS Partie(idPartie INTEGER PRIMARY KEY AUTOINCREMENT, idRencontre INTEGER NOT NULL, idJoueurA INTEGER NOT NULL, idJoueurB INTEGER NOT NULL, idJoueurW INTEGER NOT NULL, idJoueurX INTEGER NOT NULL, nbManchesGagnantes INTEGER DEFAULT 0, nbPointsParManche INTEGER DEFAULT 0, typePartie INTEGER DEFAULT 1, debut DATETIME NOT NULL, fin DATETIME, CONSTRAINT fk_idRencontre_1 FOREIGN KEY (idRencontre) REFERENCES Rencontre(idRencontre), CONSTRAINT fk_idJoueur_A FOREIGN KEY (idJoueurA) REFERENCES Joueur(numeroLicence), CONSTRAINT fk_idJoueur_B FOREIGN KEY (idJoueurB) REFERENCES Joueur(numeroLicence), CONSTRAINT fk_idJoueur_W FOREIGN KEY (idJoueurW) REFERENCES Joueur(numeroLicence), CONSTRAINT fk_idJoueur_X FOREIGN KEY (idJoueurX) REFERENCES Joueur(numeroLicence));

--- Table Score

CREATE TABLE IF NOT EXISTS Score(idPartie INTEGER NOT NULL, numeroSet INTEGER NOT NULL, pointsJoueurClubA INTEGER DEFAULT 0, pointsJoueurClubB INTEGER DEFAULT 0, debut DATETIME NOT NULL, fin DATETIME, CONSTRAINT pk_score PRIMARY KEY (idPartie,numeroSet), CONSTRAINT fk_idPartie_1 FOREIGN KEY (idPartie) REFERENCES Partie(idPartie));

--- Voir aussi :
--- ON DELETE CASCADE
