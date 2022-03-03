--- LDD (langage de définition de données)

--
-- Base de données: `areapi`
--

DROP DATABASE IF EXISTS `areapi`;

CREATE DATABASE IF NOT EXISTS `areapi`;

USE `areapi`;

-- --------------------------------------------------------

-- Création du compte d'accès à la base de données areapi

-- CREATE USER 'areapi'@'%' IDENTIFIED BY 'password';
-- GRANT ALL PRIVILEGES ON `areapi`.* TO 'areapi'@'%';
-- FLUSH PRIVILEGES;

-- --------------------------------------------------------

--- Supprime les tables

DROP TABLE IF EXISTS Score;
DROP TABLE IF EXISTS Partie;
DROP TABLE IF EXISTS Rencontre;
DROP TABLE IF EXISTS Joueur;
DROP TABLE IF EXISTS Club;

--- Table Club

CREATE TABLE IF NOT EXISTS `Club` (
  `idClub` int(11) NOT NULL AUTO_INCREMENT,
  `nomClub` varchar(255) NOT NULL,
  PRIMARY KEY (`idClub`),
  CONSTRAINT Unique_NomClub UNIQUE (`nomClub`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--- Remarque : il faudrait un concept Equipe à l'intérieur d'un Club
--- Il peut y avoir plusieurs Equipe dans un Club. Un Joueur peut probablement participer à plusieurs Equipe dans un même Club.

--- Table Joueur

CREATE TABLE IF NOT EXISTS `Joueur` (
  `numeroLicence` int(11) NOT NULL,
  `idClub` int(11) NOT NULL,
  `nom` varchar(64) NOT NULL,
  `prenom` varchar(64) NOT NULL,
  PRIMARY KEY (`numeroLicence`),
  CONSTRAINT Unique_Joueur UNIQUE (`nom`,`prenom`),
  CONSTRAINT Joueur_fk_1 FOREIGN KEY (`idClub`) REFERENCES Club(`idClub`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--- Autres :
--- Catgérorie -> V1/-50, S/-40, J1/-16, etc...
--- Classement/Points -> 17/1745, 11/1129, etc...

--- Table Rencontre

CREATE TABLE IF NOT EXISTS `Rencontre` (
  `idRencontre` int(11) NOT NULL AUTO_INCREMENT,
  `idClubA` int(11) NOT NULL,
  `idClubB` int(11) NOT NULL,
  `nbPartiesGagnantes` int(11) NOT NULL DEFAULT 0,
  `estFinie` int(11) NOT NULL DEFAULT 0,
  `horodatage` datetime NOT NULL,
  PRIMARY KEY (`idRencontre`),
  CONSTRAINT ClubA_fk_A FOREIGN KEY (`idClubA`) REFERENCES Club(`idClub`) ON DELETE CASCADE,
  CONSTRAINT ClubB_fk_B FOREIGN KEY (`idClubB`) REFERENCES Club(`idClub`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--- Table Partie

CREATE TABLE IF NOT EXISTS `Partie` (
  `idPartie` int(11) NOT NULL AUTO_INCREMENT,
  `idRencontre` int(11) NOT NULL,
  `idJoueurA` int(11) NOT NULL,
  `idJoueurB` int(11) NOT NULL,
  `idJoueurW` int(11) NOT NULL,
  `idJoueurX` int(11) NOT NULL,
  `nbManchesGagnantes` int(11) NOT NULL DEFAULT 0,
  `nbPointsParManche` int(11) NOT NULL DEFAULT 0,
  `typePartie` int(11) NOT NULL DEFAULT 1,
  `debut` datetime NOT NULL,
  `fin` datetime NULL,
  PRIMARY KEY (`idPartie`),
  CONSTRAINT Rencontre_fk_1 FOREIGN KEY (`idRencontre`) REFERENCES Rencontre(`idRencontre`) ON DELETE CASCADE,
  CONSTRAINT Joueur_fk_A FOREIGN KEY (`idJoueurA`) REFERENCES Joueur(numeroLicence) ON DELETE CASCADE,
  CONSTRAINT Joueur_fk_B FOREIGN KEY (`idJoueurB`) REFERENCES Joueur(numeroLicence) ON DELETE CASCADE,
  CONSTRAINT Joueur_fk_W FOREIGN KEY (`idJoueurW`) REFERENCES Joueur(numeroLicence) ON DELETE CASCADE,
  CONSTRAINT Joueur_fk_X FOREIGN KEY (`idJoueurX`) REFERENCES Joueur(numeroLicence) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--- Table Score

CREATE TABLE IF NOT EXISTS `Score` (
  `idPartie` int(11) NOT NULL,
  `numeroSet` int(11) NOT NULL DEFAULT 1,
  `pointsJoueurClubA` int(11) NOT NULL DEFAULT 0,
  `pointsJoueurClubB` int(11) NOT NULL DEFAULT 0,
  `debut` datetime NOT NULL,
  `fin` datetime NULL,
  PRIMARY KEY (`idPartie`,`numeroSet`),
  CONSTRAINT Partie_fk_1 FOREIGN KEY (`idPartie`) REFERENCES Partie(idPartie) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--- Voir aussi :
--- ON DELETE CASCADE
