-- MySQL dump 10.13  Distrib 5.6.22, for Win32 (x86)
--
-- Host: localhost    Database: yotanet768d
-- ------------------------------------------------------
-- Server version	5.6.26-log

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Current Database: `yotanet768d`
--

CREATE DATABASE /*!32312 IF NOT EXISTS*/ `yotanet768d` /*!40100 DEFAULT CHARACTER SET utf8 */;

USE `yotanet768d`;

--
-- Table structure for table `accelerator`
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `accelerator` (
  `accelerator_id` int(10) NOT NULL AUTO_INCREMENT,
  `name` varchar(15) NOT NULL,
  `class` varchar(1) NOT NULL,
  `points` int(10) NOT NULL,
  `credits` int(10) NOT NULL,
  `gold` int(10) NOT NULL,
  PRIMARY KEY (`accelerator_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `accelerator`
--

LOCK TABLES `accelerator` WRITE;
/*!40000 ALTER TABLE `accelerator` DISABLE KEYS */;
/*!40000 ALTER TABLE `accelerator` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `cartograph`
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `cartograph` (
  `cartograph_id` int(10) NOT NULL AUTO_INCREMENT,
  `name` varchar(15) NOT NULL,
  `class` varchar(1) NOT NULL,
  `link` int(10) NOT NULL,
  `credits` int(10) NOT NULL,
  `gold` int(10) NOT NULL,
  PRIMARY KEY (`cartograph_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `cartograph`
--

LOCK TABLES `cartograph` WRITE;
/*!40000 ALTER TABLE `cartograph` DISABLE KEYS */;
/*!40000 ALTER TABLE `cartograph` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `chinilka`
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `chinilka` (
  `chinilka_id` int(10) NOT NULL AUTO_INCREMENT,
  `name` varchar(15) NOT NULL,
  `class` varchar(1) NOT NULL,
  `energy` int(10) NOT NULL,
  `points` int(10) NOT NULL,
  `credits` int(10) NOT NULL,
  `gold` int(10) NOT NULL,
  PRIMARY KEY (`chinilka_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `chinilka`
--

LOCK TABLES `chinilka` WRITE;
/*!40000 ALTER TABLE `chinilka` DISABLE KEYS */;
/*!40000 ALTER TABLE `chinilka` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `circulatory`
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `circulatory` (
  `circulatory_id` int(10) NOT NULL AUTO_INCREMENT,
  `name` varchar(15) NOT NULL,
  `text` mediumtext NOT NULL,
  PRIMARY KEY (`circulatory_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `circulatory`
--

LOCK TABLES `circulatory` WRITE;
/*!40000 ALTER TABLE `circulatory` DISABLE KEYS */;
/*!40000 ALTER TABLE `circulatory` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `engine`
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `engine` (
  `engine_id` int(10) NOT NULL AUTO_INCREMENT,
  `name` varchar(15) NOT NULL,
  `class` varchar(1) NOT NULL,
  PRIMARY KEY (`engine_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `engine`
--

LOCK TABLES `engine` WRITE;
/*!40000 ALTER TABLE `engine` DISABLE KEYS */;
/*!40000 ALTER TABLE `engine` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `escadra`
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `escadra` (
  `escadra_id` int(10) NOT NULL AUTO_INCREMENT,
  `name` varchar(15) NOT NULL,
  `captain` int(10) NOT NULL,
  PRIMARY KEY (`escadra_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `escadra`
--

LOCK TABLES `escadra` WRITE;
/*!40000 ALTER TABLE `escadra` DISABLE KEYS */;
/*!40000 ALTER TABLE `escadra` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `eyes`
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `eyes` (
  `eyes_id` int(10) NOT NULL AUTO_INCREMENT,
  `name` varchar(15) NOT NULL,
  `text` mediumtext NOT NULL,
  PRIMARY KEY (`eyes_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `eyes`
--

LOCK TABLES `eyes` WRITE;
/*!40000 ALTER TABLE `eyes` DISABLE KEYS */;
/*!40000 ALTER TABLE `eyes` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `fuel_tank`
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `fuel_tank` (
  `fuel_tank_id` int(10) NOT NULL AUTO_INCREMENT,
  `name` varchar(15) NOT NULL,
  `class` varchar(1) NOT NULL,
  `penta` int(10) NOT NULL,
  `credits` int(10) NOT NULL,
  `gold` int(10) NOT NULL,
  PRIMARY KEY (`fuel_tank_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `fuel_tank`
--

LOCK TABLES `fuel_tank` WRITE;
/*!40000 ALTER TABLE `fuel_tank` DISABLE KEYS */;
/*!40000 ALTER TABLE `fuel_tank` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `generator`
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `generator` (
  `generator_id` int(10) NOT NULL AUTO_INCREMENT,
  `class` varchar(1) NOT NULL,
  `name` varchar(15) NOT NULL,
  `speed` int(10) NOT NULL,
  `credits` int(10) NOT NULL,
  `gold` int(10) NOT NULL,
  PRIMARY KEY (`generator_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `generator`
--

LOCK TABLES `generator` WRITE;
/*!40000 ALTER TABLE `generator` DISABLE KEYS */;
/*!40000 ALTER TABLE `generator` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `grab`
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `grab` (
  `grab_id` int(10) NOT NULL AUTO_INCREMENT,
  `name` varchar(15) NOT NULL,
  `class` varchar(1) NOT NULL,
  `energy` int(10) NOT NULL,
  `points` int(10) NOT NULL,
  `credits` int(10) NOT NULL,
  `gold` int(10) NOT NULL,
  PRIMARY KEY (`grab_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `grab`
--

LOCK TABLES `grab` WRITE;
/*!40000 ALTER TABLE `grab` DISABLE KEYS */;
/*!40000 ALTER TABLE `grab` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `hearing`
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `hearing` (
  `hearing_id` int(10) NOT NULL AUTO_INCREMENT,
  `name` varchar(15) NOT NULL,
  `text` mediumtext NOT NULL,
  PRIMARY KEY (`hearing_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `hearing`
--

LOCK TABLES `hearing` WRITE;
/*!40000 ALTER TABLE `hearing` DISABLE KEYS */;
/*!40000 ALTER TABLE `hearing` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `help`
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `help` (
  `help_id` int(10) NOT NULL AUTO_INCREMENT,
  `text` mediumtext NOT NULL,
  `level` int(10) NOT NULL,
  PRIMARY KEY (`help_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `help`
--

LOCK TABLES `help` WRITE;
/*!40000 ALTER TABLE `help` DISABLE KEYS */;
/*!40000 ALTER TABLE `help` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `human_generator`
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `human_generator` (
  `human_generator_id` int(10) NOT NULL AUTO_INCREMENT,
  `sceleton` int(10) NOT NULL,
  `muscle` int(10) NOT NULL,
  `nerves` int(10) NOT NULL,
  `eyes` int(10) NOT NULL,
  `hearing` int(10) NOT NULL,
  `scent` int(10) NOT NULL,
  `taste` int(10) NOT NULL,
  `respirator` int(10) NOT NULL,
  `circulatory` int(10) NOT NULL,
  `reproduction` int(10) NOT NULL,
  `immunity` int(10) NOT NULL,
  PRIMARY KEY (`human_generator_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `human_generator`
--

LOCK TABLES `human_generator` WRITE;
/*!40000 ALTER TABLE `human_generator` DISABLE KEYS */;
/*!40000 ALTER TABLE `human_generator` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `immunity`
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `immunity` (
  `immunity_id` int(10) NOT NULL AUTO_INCREMENT,
  `name` varchar(15) NOT NULL,
  `text` mediumtext NOT NULL,
  PRIMARY KEY (`immunity_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `immunity`
--

LOCK TABLES `immunity` WRITE;
/*!40000 ALTER TABLE `immunity` DISABLE KEYS */;
/*!40000 ALTER TABLE `immunity` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `improvement`
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `improvement` (
  `improvement_id` int(10) NOT NULL AUTO_INCREMENT,
  `name` varchar(15) NOT NULL,
  `description` mediumtext NOT NULL,
  PRIMARY KEY (`improvement_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `improvement`
--

LOCK TABLES `improvement` WRITE;
/*!40000 ALTER TABLE `improvement` DISABLE KEYS */;
/*!40000 ALTER TABLE `improvement` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `map`
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `map` (
  `map_id` int(10) NOT NULL AUTO_INCREMENT,
  `inleft` int(10) NOT NULL,
  `inright` int(10) NOT NULL,
  `intop` int(10) NOT NULL,
  `inbottom` int(10) NOT NULL,
  `infront` int(10) NOT NULL,
  `inbehind` int(10) NOT NULL,
  `data` mediumtext NOT NULL,
  PRIMARY KEY (`map_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `map`
--

LOCK TABLES `map` WRITE;
/*!40000 ALTER TABLE `map` DISABLE KEYS */;
/*!40000 ALTER TABLE `map` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `muscle`
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `muscle` (
  `mescle_id` int(10) NOT NULL AUTO_INCREMENT,
  `name` varchar(15) NOT NULL,
  `text` mediumtext NOT NULL,
  PRIMARY KEY (`mescle_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `muscle`
--

LOCK TABLES `muscle` WRITE;
/*!40000 ALTER TABLE `muscle` DISABLE KEYS */;
/*!40000 ALTER TABLE `muscle` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `nerves`
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `nerves` (
  `nerves_id` int(10) NOT NULL AUTO_INCREMENT,
  `name` varchar(15) NOT NULL,
  `text` mediumtext NOT NULL,
  PRIMARY KEY (`nerves_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `nerves`
--

LOCK TABLES `nerves` WRITE;
/*!40000 ALTER TABLE `nerves` DISABLE KEYS */;
/*!40000 ALTER TABLE `nerves` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `news`
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `news` (
  `news_id` int(10) NOT NULL AUTO_INCREMENT,
  `name` varchar(15) NOT NULL,
  `text` mediumtext NOT NULL,
  PRIMARY KEY (`news_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `news`
--

LOCK TABLES `news` WRITE;
/*!40000 ALTER TABLE `news` DISABLE KEYS */;
/*!40000 ALTER TABLE `news` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `player`
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `player` (
  `player_id` int(10) NOT NULL AUTO_INCREMENT,
  `vk_id` int(10) NOT NULL,
  `gold` int(10) NOT NULL,
  `credits` int(10) NOT NULL,
  `race` int(10) NOT NULL,
  `ship` int(10) NOT NULL,
  `spec` int(10) NOT NULL,
  `rank` int(10) NOT NULL,
  `escadra` int(10) NOT NULL,
  `rating` int(10) NOT NULL,
  `screen` int(10) NOT NULL,
  `level` int(10) NOT NULL,
  `accelerator` int(10) NOT NULL,
  `map` int(10) NOT NULL,
  PRIMARY KEY (`player_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `player`
--

LOCK TABLES `player` WRITE;
/*!40000 ALTER TABLE `player` DISABLE KEYS */;
/*!40000 ALTER TABLE `player` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `race`
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `race` (
  `race_id` int(10) NOT NULL AUTO_INCREMENT,
  `name` varchar(15) NOT NULL,
  `history` mediumtext NOT NULL,
  `head` int(10) NOT NULL,
  PRIMARY KEY (`race_id`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `race`
--

LOCK TABLES `race` WRITE;
/*!40000 ALTER TABLE `race` DISABLE KEYS */;
INSERT INTO `race` VALUES (1,'?????','??? ??????????? ?????? ?????????. ??? ???????????? ???????-??????????? ????????.',0),(2,'???????????','?????? ? ???????? ???????.',0),(3,'??????????','????? ?????.',0),(4,'??????????','???????? ? ???????? ?????????????. ????? ?????????????????? ?? ?????????? ? ??????????. ????? ?????? ????? ??????????.',0),(5,'???????','???????????? ???? ?????. ???? ??????? ?????????????.',0),(6,'????????','???????????? ??????? ????.',0),(7,'????????','??????????? ?????????.',0);
/*!40000 ALTER TABLE `race` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `radar`
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `radar` (
  `radar_id` int(10) NOT NULL AUTO_INCREMENT,
  `name` varchar(15) NOT NULL,
  `class` varchar(1) NOT NULL,
  `energy` int(10) NOT NULL,
  `ships` int(10) NOT NULL,
  `credits` int(10) NOT NULL,
  `gold` int(10) NOT NULL,
  PRIMARY KEY (`radar_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `radar`
--

LOCK TABLES `radar` WRITE;
/*!40000 ALTER TABLE `radar` DISABLE KEYS */;
/*!40000 ALTER TABLE `radar` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `rank`
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `rank` (
  `rank_id` int(10) NOT NULL AUTO_INCREMENT,
  `name` varchar(15) NOT NULL,
  `escadra_id` int(10) NOT NULL,
  `reward` int(10) NOT NULL,
  PRIMARY KEY (`rank_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `rank`
--

LOCK TABLES `rank` WRITE;
/*!40000 ALTER TABLE `rank` DISABLE KEYS */;
/*!40000 ALTER TABLE `rank` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `rating`
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `rating` (
  `rating_id` int(10) NOT NULL AUTO_INCREMENT,
  `exp` int(10) NOT NULL,
  `kills` int(10) NOT NULL,
  `death` int(10) NOT NULL,
  `mission` int(10) NOT NULL,
  `credits` int(10) NOT NULL,
  `player_id` int(10) NOT NULL,
  `fights` int(10) NOT NULL,
  PRIMARY KEY (`rating_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `rating`
--

LOCK TABLES `rating` WRITE;
/*!40000 ALTER TABLE `rating` DISABLE KEYS */;
/*!40000 ALTER TABLE `rating` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `reproduction`
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `reproduction` (
  `reproduction_id` int(10) NOT NULL AUTO_INCREMENT,
  `name` varchar(15) NOT NULL,
  `text` mediumtext NOT NULL,
  PRIMARY KEY (`reproduction_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `reproduction`
--

LOCK TABLES `reproduction` WRITE;
/*!40000 ALTER TABLE `reproduction` DISABLE KEYS */;
/*!40000 ALTER TABLE `reproduction` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `resource`
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `resource` (
  `resource_id` int(10) NOT NULL AUTO_INCREMENT,
  `name` varchar(15) NOT NULL,
  `class` varchar(1) NOT NULL,
  PRIMARY KEY (`resource_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `resource`
--

LOCK TABLES `resource` WRITE;
/*!40000 ALTER TABLE `resource` DISABLE KEYS */;
/*!40000 ALTER TABLE `resource` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `respirator`
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `respirator` (
  `respirator_id` int(10) NOT NULL AUTO_INCREMENT,
  `name` varchar(15) NOT NULL,
  `text` mediumtext NOT NULL,
  PRIMARY KEY (`respirator_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `respirator`
--

LOCK TABLES `respirator` WRITE;
/*!40000 ALTER TABLE `respirator` DISABLE KEYS */;
/*!40000 ALTER TABLE `respirator` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `reward`
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `reward` (
  `reward_id` int(10) NOT NULL AUTO_INCREMENT,
  `title` varchar(15) NOT NULL,
  `description` mediumtext NOT NULL,
  `type` int(10) NOT NULL,
  PRIMARY KEY (`reward_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `reward`
--

LOCK TABLES `reward` WRITE;
/*!40000 ALTER TABLE `reward` DISABLE KEYS */;
/*!40000 ALTER TABLE `reward` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `scaner`
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `scaner` (
  `scaner_id` int(10) NOT NULL AUTO_INCREMENT,
  `name` varchar(15) NOT NULL,
  `class` varchar(1) NOT NULL,
  `energy` int(10) NOT NULL,
  `predm` int(10) NOT NULL,
  `credits` int(10) NOT NULL,
  `gold` int(10) NOT NULL,
  PRIMARY KEY (`scaner_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `scaner`
--

LOCK TABLES `scaner` WRITE;
/*!40000 ALTER TABLE `scaner` DISABLE KEYS */;
/*!40000 ALTER TABLE `scaner` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `sceleton`
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `sceleton` (
  `sceleton_id` int(10) NOT NULL AUTO_INCREMENT,
  `name` varchar(15) NOT NULL,
  `text` mediumtext NOT NULL,
  PRIMARY KEY (`sceleton_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `sceleton`
--

LOCK TABLES `sceleton` WRITE;
/*!40000 ALTER TABLE `sceleton` DISABLE KEYS */;
/*!40000 ALTER TABLE `sceleton` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `scent`
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `scent` (
  `scent_id` int(10) NOT NULL AUTO_INCREMENT,
  `name` varchar(15) NOT NULL,
  `text` mediumtext NOT NULL,
  PRIMARY KEY (`scent_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `scent`
--

LOCK TABLES `scent` WRITE;
/*!40000 ALTER TABLE `scent` DISABLE KEYS */;
/*!40000 ALTER TABLE `scent` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `screen`
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `screen` (
  `screen_id` int(10) NOT NULL AUTO_INCREMENT,
  `width` int(10) NOT NULL,
  `height` int(10) NOT NULL,
  PRIMARY KEY (`screen_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `screen`
--

LOCK TABLES `screen` WRITE;
/*!40000 ALTER TABLE `screen` DISABLE KEYS */;
/*!40000 ALTER TABLE `screen` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ship`
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ship` (
  `ship_id` int(10) NOT NULL AUTO_INCREMENT,
  `name` varchar(15) NOT NULL,
  `class` varchar(1) NOT NULL,
  `engine` int(10) NOT NULL,
  `energy` int(10) NOT NULL,
  `life` int(10) NOT NULL,
  `fuel_tank` int(10) NOT NULL,
  PRIMARY KEY (`ship_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ship`
--

LOCK TABLES `ship` WRITE;
/*!40000 ALTER TABLE `ship` DISABLE KEYS */;
/*!40000 ALTER TABLE `ship` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ship_body`
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ship_body` (
  `body_id` int(10) NOT NULL AUTO_INCREMENT,
  `name` varchar(15) NOT NULL,
  `class` varchar(1) NOT NULL,
  `energy` int(10) NOT NULL,
  `credits` int(10) NOT NULL,
  `gold` int(10) NOT NULL,
  PRIMARY KEY (`body_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ship_body`
--

LOCK TABLES `ship_body` WRITE;
/*!40000 ALTER TABLE `ship_body` DISABLE KEYS */;
/*!40000 ALTER TABLE `ship_body` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `spec`
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `spec` (
  `spec_id` int(10) NOT NULL AUTO_INCREMENT,
  `name` varchar(15) NOT NULL,
  PRIMARY KEY (`spec_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `spec`
--

LOCK TABLES `spec` WRITE;
/*!40000 ALTER TABLE `spec` DISABLE KEYS */;
/*!40000 ALTER TABLE `spec` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `taste`
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `taste` (
  `taste_id` int(10) NOT NULL AUTO_INCREMENT,
  `name` varchar(15) NOT NULL,
  `text` mediumtext NOT NULL,
  PRIMARY KEY (`taste_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `taste`
--

LOCK TABLES `taste` WRITE;
/*!40000 ALTER TABLE `taste` DISABLE KEYS */;
/*!40000 ALTER TABLE `taste` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `weapons`
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `weapons` (
  `weapons_id` int(10) NOT NULL AUTO_INCREMENT,
  `name` varchar(15) NOT NULL,
  `class` varchar(1) NOT NULL,
  `energy` int(10) NOT NULL,
  `fire` int(10) NOT NULL,
  `speed` int(10) NOT NULL,
  `link` int(10) NOT NULL,
  `credits` int(10) NOT NULL,
  `gold` int(10) NOT NULL,
  PRIMARY KEY (`weapons_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `weapons`
--

LOCK TABLES `weapons` WRITE;
/*!40000 ALTER TABLE `weapons` DISABLE KEYS */;
/*!40000 ALTER TABLE `weapons` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `world`
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `world` (
  `id` int(10) NOT NULL AUTO_INCREMENT,
  `penta` int(10) NOT NULL,
  `yota` int(10) NOT NULL,
  `sector_length` int(10) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `world`
--

LOCK TABLES `world` WRITE;
/*!40000 ALTER TABLE `world` DISABLE KEYS */;
/*!40000 ALTER TABLE `world` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `yotanet`
--

/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `yotanet` (
  `yotanet_id` int(10) NOT NULL AUTO_INCREMENT,
  `class` varchar(1) NOT NULL,
  `name` varchar(15) NOT NULL,
  `speed` int(10) NOT NULL,
  `credits` int(10) NOT NULL,
  `gold` int(10) NOT NULL,
  PRIMARY KEY (`yotanet_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `yotanet`
--

LOCK TABLES `yotanet` WRITE;
/*!40000 ALTER TABLE `yotanet` DISABLE KEYS */;
/*!40000 ALTER TABLE `yotanet` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2015-08-24 20:00:26
