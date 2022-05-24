--- LMD (langage de manipulation de données)

--- Contenu des tables (tests)

--- Table Club

INSERT INTO Club (idClub, nomClub) VALUES (NULL,'PPC Avignon');
INSERT INTO Club (idClub, nomClub) VALUES (NULL,'PPC Pernes');
INSERT INTO Club (idClub, nomClub) VALUES (NULL,'PPC Sorgues');
INSERT INTO Club (idClub, nomClub) VALUES (NULL,'AS Cavaillon TT');
INSERT INTO Club (idClub, nomClub) VALUES (NULL,'C.S. Pertuis');
INSERT INTO Club (idClub, nomClub) VALUES (NULL,'T.T. Morières');

--- Table Joueur

INSERT INTO Joueur(numeroLicence, idClub, nom, prenom) VALUES (9419829,1,'BOUDRIMIL','Kamal');
INSERT INTO Joueur(numeroLicence, idClub, nom, prenom) VALUES (844443,1,'REDOR','Simon');
INSERT INTO Joueur(numeroLicence, idClub, nom, prenom) VALUES (843368,1,'KRIER','Eric');
INSERT INTO Joueur(numeroLicence, idClub, nom, prenom) VALUES (139328,1,'RUIZ','Jean michel');
INSERT INTO Joueur(numeroLicence, idClub, nom, prenom) VALUES (841827,1,'GUIDARELLI','Nicolas');
INSERT INTO Joueur(numeroLicence, idClub, nom, prenom) VALUES (9420542,2,'RUAULT','Nicolas');
INSERT INTO Joueur(numeroLicence, idClub, nom, prenom) VALUES (845682,2,'CROUZET','Lionel');
INSERT INTO Joueur(numeroLicence, idClub, nom, prenom) VALUES (847650,2,'FLORES','Fabien');
INSERT INTO Joueur(numeroLicence, idClub, nom, prenom) VALUES (845423,2,'BRESSON','Thibault');
INSERT INTO Joueur(numeroLicence, idClub, nom, prenom) VALUES (844549,2,'FAGOO','Damien');
INSERT INTO Joueur(numeroLicence, idClub, nom, prenom) VALUES (843944,3,'BEAUMONT','Jérôme');
INSERT INTO Joueur(numeroLicence, idClub, nom, prenom) VALUES (303504,3,'SAULNIER','Christian');
INSERT INTO Joueur(numeroLicence, idClub, nom, prenom) VALUES (842353,3,'COMTE','Emmanuel');
INSERT INTO Joueur(numeroLicence, idClub, nom, prenom) VALUES (842363,3,'LEVRARD','Mickael');
INSERT INTO Joueur(numeroLicence, idClub, nom, prenom) VALUES (645758,3,'FILAFERRO','Thomas');
INSERT INTO Joueur(numeroLicence, idClub, nom, prenom) VALUES (846543,3,'DUBOURG ','Dylan');
INSERT INTO Joueur(numeroLicence, idClub, nom, prenom) VALUES (841424,4,'ALBERT','Pierre-david');
INSERT INTO Joueur(numeroLicence, idClub, nom, prenom) VALUES (843634,4,'MANGIN','Frederic');
INSERT INTO Joueur(numeroLicence, idClub, nom, prenom) VALUES (9110467,4,'ZENATY','Julien');
INSERT INTO Joueur(numeroLicence, idClub, nom, prenom) VALUES (843871,4,'MANGIN','Thierry');
INSERT INTO Joueur(numeroLicence, idClub, nom, prenom) VALUES (842471,4,'DESPRES','Gregory');
INSERT INTO Joueur(numeroLicence, idClub, nom, prenom) VALUES (3330232,5,'BADRE','Corentin');
INSERT INTO Joueur(numeroLicence, idClub, nom, prenom) VALUES (845470,5,'CHOUISNARD','Enzo');
INSERT INTO Joueur(numeroLicence, idClub, nom, prenom) VALUES (261769,5,'LASCOMBE','Nicolas');
INSERT INTO Joueur(numeroLicence, idClub, nom, prenom) VALUES (845078,5,'BOINARD','Thomas');
INSERT INTO Joueur(numeroLicence, idClub, nom, prenom) VALUES (84326,5,'SOLER','Michel');
INSERT INTO Joueur(numeroLicence, idClub, nom, prenom) VALUES (305731,6,'OPEZZO','Mathieu');
INSERT INTO Joueur(numeroLicence, idClub, nom, prenom) VALUES (1310341,6,'AMBROSINO','Stephane');
INSERT INTO Joueur(numeroLicence, idClub, nom, prenom) VALUES (136310,6,'MALET','Sebastien');
INSERT INTO Joueur(numeroLicence, idClub, nom, prenom) VALUES (349167,6,'ROUTTIER','Julien');
INSERT INTO Joueur(numeroLicence, idClub, nom, prenom) VALUES (43041,6,'JOULLIE','Arnaud');

--- Table Rencontre

INSERT INTO Rencontre(idRencontre, idClubA, idClubW, nbPartiesGagnantes, estFinie, horodatage) VALUES (NULL,3,1,8,0,'2022-01-29 08:00:00');

--- Table Partie

INSERT INTO Partie(idPartie, idRencontre, idJoueurA, idJoueurB, idJoueurW, idJoueurX, nbManchesGagnantes, nbPointsParManche, typePartie, debut) VALUES (NULL,1,843944,9419829,843944,9419829,3,11,1,'2022-01-29 08:15:00');
INSERT INTO Partie(idPartie, idRencontre, idJoueurA, idJoueurB, idJoueurW, idJoueurX, nbManchesGagnantes, nbPointsParManche, typePartie, debut) VALUES (NULL,1,303504,844443,303504,844443,3,11,1,'2022-01-29 08:15:00');
INSERT INTO Partie(idPartie, idRencontre, idJoueurA, idJoueurB, idJoueurW, idJoueurX, nbManchesGagnantes, nbPointsParManche, typePartie, debut) VALUES (NULL,1,843944,303504,9419829,844443,3,11,2,'2022-01-29 08:15:00');

--- Table Score

INSERT INTO Score(idPartie, numeroSet, pointsJoueurClubA, pointsJoueurClubW, debut) VALUES (1,1,11,5,'2022-01-29 08:15:00');
INSERT INTO Score(idPartie, numeroSet, pointsJoueurClubA, pointsJoueurClubW, debut) VALUES (1,2,0,0,'2022-01-29 08:25:00');

