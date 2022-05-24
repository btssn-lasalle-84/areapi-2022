--- Exemples de requêtes SQL

--- Liste des clubs

SELECT * FROM Club;

SELECT COUNT(*) AS NbClubs FROM Club;

--- Liste des joueurs

SELECT * FROM Joueur;

SELECT COUNT(*) AS NbJoueurs FROM Joueur;

SELECT nom || ' ' || prenom AS NomJoueur FROM Joueur ORDER BY NomJoueur;

SELECT * FROM Joueur 
INNER JOIN Club ON Joueur.idClub=Club.idClub;

SELECT Joueur.numeroLicence, Joueur.nom, Joueur.prenom, Club.nomClub FROM Joueur 
INNER JOIN Club ON Joueur.idClub=Club.idClub 
ORDER BY Club.nomClub ASC;

--- Liste des joueurs pour un club

SELECT * FROM Joueur 
INNER JOIN Club ON Joueur.idClub=Club.idClub 
WHERE Club.idClub='3';

SELECT * FROM Joueur 
INNER JOIN Club ON Joueur.idClub=Club.idClub 
WHERE Club.idClub='3' ORDER BY Joueur.nom ASC;

SELECT Joueur.numeroLicence, Joueur.nom, Joueur.prenom, Club.nomClub FROM Joueur 
INNER JOIN Club ON Joueur.idClub=Club.idClub 
WHERE Club.idClub='3';

SELECT Joueur.numeroLicence, Joueur.nom, Joueur.prenom, Club.nomClub FROM Joueur 
INNER JOIN Club ON Joueur.idClub=Club.idClub 
WHERE Club.idClub='3' ORDER BY Joueur.nom ASC;

--- Liste des rencontres

SELECT * FROM Rencontre;

SELECT * FROM Rencontre 
INNER JOIN Club a ON (a.idClub = Rencontre.idClubA) 
INNER JOIN Club b ON (b.idClub = Rencontre.idClubW);

SELECT Rencontre.*, a.nomClub, b.nomClub FROM Rencontre 
INNER JOIN Club a ON (a.idClub = Rencontre.idClubA) 
INNER JOIN Club b ON (b.idClub = Rencontre.idClubW);

--- Terminer une rencontre

UPDATE Rencontre SET estFinie=1 WHERE idRencontre='1';

--- Liste des parties

SELECT * FROM Partie;

--- Liste des parties pour une rencontre

--- Liste de toutes parties pour une rencontre

SELECT * FROM Partie INNER JOIN Rencontre ON Partie.idRencontre = Rencontre.idRencontre 
INNER JOIN Club ClubA ON (ClubA.idClub = Rencontre.idClubA) 
INNER JOIN Club ClubW ON (ClubW.idClub = Rencontre.idClubW) 
WHERE Rencontre.idRencontre='1';

--- Liste de toutes parties SIMPLE pour une rencontre

SELECT * FROM Partie 
INNER JOIN Rencontre ON Partie.idRencontre = Rencontre.idRencontre 
INNER JOIN Club ClubA ON (ClubA.idClub = Rencontre.idClubA) 
INNER JOIN Club ClubW ON (ClubW.idClub = Rencontre.idClubW) 
WHERE Rencontre.idRencontre='1' AND Partie.typePartie='1';

--- Liste de toutes parties DOUBLE pour une rencontre

SELECT * FROM Partie 
INNER JOIN Rencontre ON Partie.idRencontre = Rencontre.idRencontre 
INNER JOIN Club ClubA ON (ClubA.idClub = Rencontre.idClubA) 
INNER JOIN Club ClubW ON (ClubW.idClub = Rencontre.idClubW) 
WHERE Rencontre.idRencontre='1' AND Partie.typePartie='2';

--- Liste de toutes parties SIMPLE pour une rencontre avec les noms des joueurs

SELECT * FROM Partie 
INNER JOIN Joueur joueurA ON (joueurA.numeroLicence = Partie.idJoueurA) 
INNER JOIN Joueur joueurB ON (joueurB.numeroLicence = Partie.idJoueurB) 
INNER JOIN Rencontre ON Partie.idRencontre = Rencontre.idRencontre 
INNER JOIN Club ClubA ON (ClubA.idClub = Rencontre.idClubA) 
INNER JOIN Club ClubW ON (ClubW.idClub = Rencontre.idClubW) 
WHERE Rencontre.idRencontre='1' AND Partie.typePartie='1';

--- Score d'une partie d'une rencontre

SELECT Score.debut, Score.numeroSet, joueurA.numeroLicence, joueurA.nom, joueurA.prenom, ClubA.nomClub, Score.pointsJoueurClubA, Score.pointsJoueurClubW, joueurB.numeroLicence, joueurB.nom, joueurB.prenom, ClubW.nomClub FROM Partie
INNER JOIN Joueur joueurA ON (joueurA.numeroLicence = Partie.idJoueurA)
INNER JOIN Joueur joueurB ON (joueurB.numeroLicence = Partie.idJoueurB)
INNER JOIN Rencontre ON Partie.idRencontre = Rencontre.idRencontre
INNER JOIN Club ClubA ON (ClubA.idClub = Rencontre.idClubA)
INNER JOIN Club ClubW ON (ClubW.idClub = Rencontre.idClubW)
INNER JOIN Score ON Score.idPartie = Partie.idPartie
WHERE Rencontre.idRencontre='1' AND Partie.idPartie = '1';

---- Commencer un set

INSERT INTO Score(idPartie,numeroSet, pointsJoueurClubA, pointsJoueurClubW, debut) VALUES (1,3,0,0,DATETIME('now'));

---- Finir un set et enregistrer le score

UPDATE Score SET fin=DATETIME('now'), pointsJoueurClubA='11', pointsJoueurClubW='9' WHERE idPartie='1' AND numeroSet='3';

--- Terminer une partie

UPDATE Partie SET fin=DATETIME('now') WHERE idPartie='1';
