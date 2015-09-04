-- phpMyAdmin SQL Dump
-- version 4.4.14
-- http://www.phpmyadmin.net
--
-- Хост: localhost
-- Время создания: Сен 04 2015 г., 10:33
-- Версия сервера: 5.5.44-MariaDB
-- Версия PHP: 5.4.16

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- База данных: `yotanet768d`
--

-- --------------------------------------------------------

--
-- Структура таблицы `accelerator`
--

CREATE TABLE IF NOT EXISTS `accelerator` (
  `accelerator_id` int(10) NOT NULL,
  `name` varchar(15) NOT NULL,
  `class` varchar(1) NOT NULL,
  `points` int(10) NOT NULL,
  `credits` int(10) NOT NULL,
  `gold` int(10) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8;

--
-- Дамп данных таблицы `accelerator`
--

INSERT INTO `accelerator` (`accelerator_id`, `name`, `class`, `points`, `credits`, `gold`) VALUES
(1, 'простой', 'A', 5, 100, 10000),
(2, 'улучшенный', 'B', 10, 200, 20000),
(3, 'экстра', 'C', 15, 300, 30000),
(4, 'быстрый', 'D', 20, 400, 40000),
(5, 'скоростной', 'E', 25, 500, 50000),
(6, 'реактивный', 'F', 30, 600, 60000),
(7, 'плазменный', 'G', 35, 700, 70000);

-- --------------------------------------------------------

--
-- Структура таблицы `cartograph`
--

CREATE TABLE IF NOT EXISTS `cartograph` (
  `cartograph_id` int(10) NOT NULL,
  `name` varchar(15) NOT NULL,
  `class` varchar(1) NOT NULL,
  `energy` int(10) NOT NULL,
  `link` int(10) NOT NULL,
  `credits` int(10) NOT NULL,
  `gold` int(10) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;

--
-- Дамп данных таблицы `cartograph`
--

INSERT INTO `cartograph` (`cartograph_id`, `name`, `class`, `energy`, `link`, `credits`, `gold`) VALUES
(1, 'малый', 'A', 10, 10, 100, 10000),
(2, 'средний', 'B', 30, 30, 200, 20000),
(3, 'стандартный', 'С', 50, 50, 300, 30000),
(4, 'длинный', 'D', 100, 75, 400, 40000);

-- --------------------------------------------------------

--
-- Структура таблицы `chinilka`
--

CREATE TABLE IF NOT EXISTS `chinilka` (
  `chinilka_id` int(10) NOT NULL,
  `name` varchar(15) NOT NULL,
  `class` varchar(1) NOT NULL,
  `energy` int(10) NOT NULL,
  `points` int(10) NOT NULL,
  `credits` int(10) NOT NULL,
  `gold` int(10) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8;

--
-- Дамп данных таблицы `chinilka`
--

INSERT INTO `chinilka` (`chinilka_id`, `name`, `class`, `energy`, `points`, `credits`, `gold`) VALUES
(1, 'диплоид', 'A', 50, 20, 100, 10000),
(2, 'триплоид', 'B', 100, 30, 200, 20000),
(3, 'пентоплоид', 'C', 150, 50, 300, 30000),
(4, 'матаплоид', 'D', 200, 75, 400, 40000),
(5, 'истоплоид', 'E', 250, 100, 500, 50000),
(6, 'устоплоид', 'F', 300, 125, 600, 60000);

-- --------------------------------------------------------

--
-- Структура таблицы `circulatory`
--

CREATE TABLE IF NOT EXISTS `circulatory` (
  `circulatory_id` int(10) NOT NULL,
  `name` varchar(15) NOT NULL,
  `text` mediumtext NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Структура таблицы `engine`
--

CREATE TABLE IF NOT EXISTS `engine` (
  `engine_id` int(10) NOT NULL,
  `name` varchar(15) NOT NULL,
  `class` varchar(1) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8;

--
-- Дамп данных таблицы `engine`
--

INSERT INTO `engine` (`engine_id`, `name`, `class`) VALUES
(2, 'Позитронный', 'A'),
(3, 'Нейронный', 'B'),
(4, 'Фильтронный', 'C'),
(5, 'Оксонный', 'D');

-- --------------------------------------------------------

--
-- Структура таблицы `escadra`
--

CREATE TABLE IF NOT EXISTS `escadra` (
  `escadra_id` int(10) NOT NULL,
  `name` varchar(15) NOT NULL,
  `captain` int(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Структура таблицы `eyes`
--

CREATE TABLE IF NOT EXISTS `eyes` (
  `eyes_id` int(10) NOT NULL,
  `name` varchar(15) NOT NULL,
  `text` mediumtext NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Структура таблицы `fuel_tank`
--

CREATE TABLE IF NOT EXISTS `fuel_tank` (
  `fuel_tank_id` int(10) NOT NULL,
  `name` varchar(15) NOT NULL,
  `class` varchar(1) NOT NULL,
  `penta` int(10) NOT NULL,
  `credits` int(10) NOT NULL,
  `gold` int(10) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;

--
-- Дамп данных таблицы `fuel_tank`
--

INSERT INTO `fuel_tank` (`fuel_tank_id`, `name`, `class`, `penta`, `credits`, `gold`) VALUES
(1, 'малый', 'A', 25, 0, 0),
(2, 'средний', 'B', 50, 100, 10000),
(3, 'большой', 'C', 75, 200, 20000),
(4, 'мегабак', 'D', 100, 300, 30000);

-- --------------------------------------------------------

--
-- Структура таблицы `generator`
--

CREATE TABLE IF NOT EXISTS `generator` (
  `generator_id` int(10) NOT NULL,
  `class` varchar(1) NOT NULL,
  `name` varchar(15) NOT NULL,
  `speed` int(10) NOT NULL,
  `credits` int(10) NOT NULL,
  `gold` int(10) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;

--
-- Дамп данных таблицы `generator`
--

INSERT INTO `generator` (`generator_id`, `class`, `name`, `speed`, `credits`, `gold`) VALUES
(1, 'A', 'эталон', 175, 100, 10000),
(2, 'B', 'энергичный', 200, 200, 20000),
(3, 'C', 'триэнергичный', 300, 300, 30000),
(4, 'D', 'тэтраэнергичный', 400, 400, 40000);

-- --------------------------------------------------------

--
-- Структура таблицы `grab`
--

CREATE TABLE IF NOT EXISTS `grab` (
  `grab_id` int(10) NOT NULL,
  `name` varchar(15) NOT NULL,
  `class` varchar(1) NOT NULL,
  `energy` int(10) NOT NULL,
  `points` int(10) NOT NULL,
  `credits` int(10) NOT NULL,
  `gold` int(10) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8;

--
-- Дамп данных таблицы `grab`
--

INSERT INTO `grab` (`grab_id`, `name`, `class`, `energy`, `points`, `credits`, `gold`) VALUES
(1, 'простой', 'A', 20, 3, 100, 10000),
(2, 'улучшенный', 'B', 30, 5, 200, 20000),
(3, 'лучший', 'C', 40, 10, 300, 30000),
(4, 'самый лучший', 'D', 100, 25, 400, 40000),
(5, 'сложный', 'E', 200, 50, 500, 50000),
(6, 'самый сложный', 'F', 300, 100, 600, 60000);

-- --------------------------------------------------------

--
-- Структура таблицы `hearing`
--

CREATE TABLE IF NOT EXISTS `hearing` (
  `hearing_id` int(10) NOT NULL,
  `name` varchar(15) NOT NULL,
  `text` mediumtext NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Структура таблицы `help`
--

CREATE TABLE IF NOT EXISTS `help` (
  `help_id` int(10) NOT NULL,
  `text` mediumtext NOT NULL,
  `level` int(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Структура таблицы `human_generator`
--

CREATE TABLE IF NOT EXISTS `human_generator` (
  `human_generator_id` int(10) NOT NULL,
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
  `immunity` int(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Структура таблицы `immunity`
--

CREATE TABLE IF NOT EXISTS `immunity` (
  `immunity_id` int(10) NOT NULL,
  `name` varchar(15) NOT NULL,
  `text` mediumtext NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Структура таблицы `improvement`
--

CREATE TABLE IF NOT EXISTS `improvement` (
  `improvement_id` int(10) NOT NULL,
  `name` varchar(15) NOT NULL,
  `description` mediumtext NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Структура таблицы `map`
--

CREATE TABLE IF NOT EXISTS `map` (
  `map_id` int(10) NOT NULL,
  `inleft` int(10) NOT NULL,
  `inright` int(10) NOT NULL,
  `intop` int(10) NOT NULL,
  `inbottom` int(10) NOT NULL,
  `infront` int(10) NOT NULL,
  `inbehind` int(10) NOT NULL,
  `data` mediumtext NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;

--
-- Дамп данных таблицы `map`
--

INSERT INTO `map` (`map_id`, `inleft`, `inright`, `intop`, `inbottom`, `infront`, `inbehind`, `data`) VALUES
(1, 0, 0, 0, 0, 0, 0, '                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                .');

-- --------------------------------------------------------

--
-- Структура таблицы `muscle`
--

CREATE TABLE IF NOT EXISTS `muscle` (
  `mescle_id` int(10) NOT NULL,
  `name` varchar(15) NOT NULL,
  `text` mediumtext NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Структура таблицы `nerves`
--

CREATE TABLE IF NOT EXISTS `nerves` (
  `nerves_id` int(10) NOT NULL,
  `name` varchar(15) NOT NULL,
  `text` mediumtext NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Структура таблицы `news`
--

CREATE TABLE IF NOT EXISTS `news` (
  `news_id` int(10) NOT NULL,
  `name` varchar(15) NOT NULL,
  `text` mediumtext NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Структура таблицы `player`
--

CREATE TABLE IF NOT EXISTS `player` (
  `player_id` int(10) NOT NULL,
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
  `map` int(10) NOT NULL,
  `pos` int(10) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;

--
-- Дамп данных таблицы `player`
--

INSERT INTO `player` (`player_id`, `vk_id`, `gold`, `credits`, `race`, `ship`, `spec`, `rank`, `escadra`, `rating`, `screen`, `level`, `map`, `pos`) VALUES
(1, 164605891, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

-- --------------------------------------------------------

--
-- Структура таблицы `protection`
--

CREATE TABLE IF NOT EXISTS `protection` (
  `protection_id` int(10) NOT NULL,
  `name` varchar(15) NOT NULL,
  `class` varchar(1) NOT NULL,
  `energy` int(10) NOT NULL,
  `life` int(10) NOT NULL,
  `credits` int(10) NOT NULL,
  `gold` int(10) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8;

--
-- Дамп данных таблицы `protection`
--

INSERT INTO `protection` (`protection_id`, `name`, `class`, `energy`, `life`, `credits`, `gold`) VALUES
(1, 'слабая', 'A', 100, 50, 100, 10000),
(2, 'средняя', 'B', 150, 150, 200, 20000),
(3, 'хорошая', 'C', 200, 300, 300, 30000),
(4, 'лучшая', 'D', 250, 500, 400, 40000),
(5, 'плазменная', 'E', 300, 600, 500, 50000),
(6, 'бронеплазменная', 'F', 350, 750, 600, 60000),
(7, 'стелсплазменная', 'G', 400, 1000, 700, 70000);

-- --------------------------------------------------------

--
-- Структура таблицы `race`
--

CREATE TABLE IF NOT EXISTS `race` (
  `race_id` int(10) NOT NULL,
  `name` varchar(15) NOT NULL,
  `history` mediumtext NOT NULL,
  `head` int(10) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8;

--
-- Дамп данных таблицы `race`
--

INSERT INTO `race` (`race_id`, `name`, `history`, `head`) VALUES
(1, 'Харха', 'Это продвинутые плазма органоиды. Это своеобразные киберго-независимые существа.', 0),
(2, 'Лайттруверы', 'Силачи с огненной планеты.', 0),
(3, 'Шерохомоты', 'Звери фурри.', 0),
(4, 'Ливербэйлы', 'Существа с реакцией гиперпортации. Умеют гиперпортироваться от субстенций к субстенции. Живут всегда возле субстенции.', 0),
(5, 'Киберги', 'Недоразвитая раса людей. Раса создана человечеством.', 0),
(6, 'Галогены', 'Уничтожители людской расы.', 0),
(7, 'Матофиты', 'Специалисты улучшений.', 0);

-- --------------------------------------------------------

--
-- Структура таблицы `radar`
--

CREATE TABLE IF NOT EXISTS `radar` (
  `radar_id` int(10) NOT NULL,
  `name` varchar(15) NOT NULL,
  `class` varchar(1) NOT NULL,
  `energy` int(10) NOT NULL,
  `ships` int(10) NOT NULL,
  `credits` int(10) NOT NULL,
  `gold` int(10) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8;

--
-- Дамп данных таблицы `radar`
--

INSERT INTO `radar` (`radar_id`, `name`, `class`, `energy`, `ships`, `credits`, `gold`) VALUES
(1, 'простой', 'A', 20, 2, 100, 10000),
(2, 'улучшенный', 'B', 40, 5, 200, 20000),
(3, 'средний', 'С', 80, 10, 300, 30000),
(4, 'лучший', 'D', 400, 50, 400, 40000),
(5, 'самый лучший', 'E', 700, 100, 500, 50000);

-- --------------------------------------------------------

--
-- Структура таблицы `rank`
--

CREATE TABLE IF NOT EXISTS `rank` (
  `rank_id` int(10) NOT NULL,
  `name` varchar(15) NOT NULL,
  `escadra_id` int(10) NOT NULL,
  `reward` int(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Структура таблицы `rating`
--

CREATE TABLE IF NOT EXISTS `rating` (
  `rating_id` int(10) NOT NULL,
  `exp` int(10) NOT NULL,
  `kills` int(10) NOT NULL,
  `death` int(10) NOT NULL,
  `mission` int(10) NOT NULL,
  `credits` int(10) NOT NULL,
  `player_id` int(10) NOT NULL,
  `fights` int(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Структура таблицы `reproduction`
--

CREATE TABLE IF NOT EXISTS `reproduction` (
  `reproduction_id` int(10) NOT NULL,
  `name` varchar(15) NOT NULL,
  `text` mediumtext NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Структура таблицы `resource`
--

CREATE TABLE IF NOT EXISTS `resource` (
  `resource_id` int(10) NOT NULL,
  `name` varchar(15) NOT NULL,
  `class` varchar(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Структура таблицы `respirator`
--

CREATE TABLE IF NOT EXISTS `respirator` (
  `respirator_id` int(10) NOT NULL,
  `name` varchar(15) NOT NULL,
  `text` mediumtext NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Структура таблицы `reward`
--

CREATE TABLE IF NOT EXISTS `reward` (
  `reward_id` int(10) NOT NULL,
  `title` varchar(15) NOT NULL,
  `description` mediumtext NOT NULL,
  `type` int(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Структура таблицы `scaner`
--

CREATE TABLE IF NOT EXISTS `scaner` (
  `scaner_id` int(10) NOT NULL,
  `name` varchar(15) NOT NULL,
  `class` varchar(1) NOT NULL,
  `energy` int(10) NOT NULL,
  `predm` int(10) NOT NULL,
  `credits` int(10) NOT NULL,
  `gold` int(10) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8;

--
-- Дамп данных таблицы `scaner`
--

INSERT INTO `scaner` (`scaner_id`, `name`, `class`, `energy`, `predm`, `credits`, `gold`) VALUES
(1, 'простой', 'A', 20, 5, 100, 10000),
(2, 'наружный', 'B', 30, 10, 200, 20000),
(3, 'плазменный', 'С', 40, 15, 300, 30000),
(4, 'йота', 'D', 50, 20, 400, 40000),
(5, 'нейра', 'E', 60, 30, 500, 50000);

-- --------------------------------------------------------

--
-- Структура таблицы `sceleton`
--

CREATE TABLE IF NOT EXISTS `sceleton` (
  `sceleton_id` int(10) NOT NULL,
  `name` varchar(15) NOT NULL,
  `text` mediumtext NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Структура таблицы `scent`
--

CREATE TABLE IF NOT EXISTS `scent` (
  `scent_id` int(10) NOT NULL,
  `name` varchar(15) NOT NULL,
  `text` mediumtext NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Структура таблицы `screen`
--

CREATE TABLE IF NOT EXISTS `screen` (
  `screen_id` int(10) NOT NULL,
  `width` int(10) NOT NULL,
  `height` int(10) NOT NULL,
  `len` int(10) NOT NULL,
  `player_id` int(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Структура таблицы `ship`
--

CREATE TABLE IF NOT EXISTS `ship` (
  `ship_id` int(10) NOT NULL,
  `player_id` int(10) NOT NULL,
  `engine` int(10) NOT NULL,
  `fuel_tank` int(10) NOT NULL,
  `yotanet` int(10) NOT NULL,
  `generator` int(10) NOT NULL,
  `cartograph` int(10) NOT NULL,
  `ship_body` int(10) NOT NULL,
  `radar` int(10) NOT NULL,
  `scaner` int(10) NOT NULL,
  `chinilka` int(10) NOT NULL,
  `grab` int(10) NOT NULL,
  `weapons` int(10) NOT NULL,
  `improvement` int(10) NOT NULL,
  `accelerator` int(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Структура таблицы `ship_body`
--

CREATE TABLE IF NOT EXISTS `ship_body` (
  `body_id` int(10) NOT NULL,
  `name` varchar(15) NOT NULL,
  `class` varchar(1) NOT NULL,
  `energy` int(10) NOT NULL,
  `life` int(10) NOT NULL,
  `credits` int(10) NOT NULL,
  `gold` int(10) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8;

--
-- Дамп данных таблицы `ship_body`
--

INSERT INTO `ship_body` (`body_id`, `name`, `class`, `energy`, `life`, `credits`, `gold`) VALUES
(1, 'легкий', 'A', 500, 200, 0, 0),
(2, 'полулегкий', 'B', 750, 300, 100, 10000),
(3, 'тяжелый', 'С', 1000, 500, 200, 20000),
(4, 'крейсер', 'D', 1250, 700, 300, 30000),
(5, 'грузовой', 'E', 2000, 1000, 400, 40000);

-- --------------------------------------------------------

--
-- Структура таблицы `spec`
--

CREATE TABLE IF NOT EXISTS `spec` (
  `spec_id` int(10) NOT NULL,
  `name` varchar(15) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8;

--
-- Дамп данных таблицы `spec`
--

INSERT INTO `spec` (`spec_id`, `name`) VALUES
(1, 'гуманоид'),
(2, 'репортер'),
(3, 'писатель'),
(4, 'ижненер'),
(5, 'админ'),
(6, 'создатель');

-- --------------------------------------------------------

--
-- Структура таблицы `taste`
--

CREATE TABLE IF NOT EXISTS `taste` (
  `taste_id` int(10) NOT NULL,
  `name` varchar(15) NOT NULL,
  `text` mediumtext NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Структура таблицы `weapons`
--

CREATE TABLE IF NOT EXISTS `weapons` (
  `weapons_id` int(10) NOT NULL,
  `player_id` int(10) NOT NULL,
  `name` varchar(15) NOT NULL,
  `class` varchar(1) NOT NULL,
  `energy` int(10) NOT NULL,
  `fire` int(10) NOT NULL,
  `speed` int(10) NOT NULL,
  `link` int(10) NOT NULL,
  `credits` int(10) NOT NULL,
  `gold` int(10) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8;

--
-- Дамп данных таблицы `weapons`
--

INSERT INTO `weapons` (`weapons_id`, `player_id`, `name`, `class`, `energy`, `fire`, `speed`, `link`, `credits`, `gold`) VALUES
(1, 0, 'протонная', 'A', 20, 5, 1, 1, 100, 10000),
(2, 0, 'нейтронная', 'B', 30, 10, 5, 5, 200, 20000),
(3, 0, 'лазер', 'С', 50, 25, 10, 10, 300, 30000),
(4, 0, 'квебек', 'D', 100, 35, 15, 15, 400, 40000),
(5, 0, 'рапира', 'E', 150, 40, 20, 20, 500, 50000),
(6, 0, 'аскорбелл', 'F', 200, 45, 25, 25, 600, 60000),
(7, 0, 'торпеды', 'G', 300, 50, 30, 30, 700, 70000);

-- --------------------------------------------------------

--
-- Структура таблицы `world`
--

CREATE TABLE IF NOT EXISTS `world` (
  `id` int(10) NOT NULL,
  `penta` int(10) NOT NULL,
  `yota` int(10) NOT NULL,
  `sector_length` int(10) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;

--
-- Дамп данных таблицы `world`
--

INSERT INTO `world` (`id`, `penta`, `yota`, `sector_length`) VALUES
(1, 12, 100, 768);

-- --------------------------------------------------------

--
-- Структура таблицы `yotanet`
--

CREATE TABLE IF NOT EXISTS `yotanet` (
  `yotanet_id` int(10) NOT NULL,
  `class` varchar(1) NOT NULL,
  `name` varchar(15) NOT NULL,
  `speed` int(10) NOT NULL,
  `credits` int(10) NOT NULL,
  `gold` int(10) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8;

--
-- Дамп данных таблицы `yotanet`
--

INSERT INTO `yotanet` (`yotanet_id`, `class`, `name`, `speed`, `credits`, `gold`) VALUES
(1, 'A', 'быстрый', 50, 100, 10000),
(2, 'B', 'скоростной', 75, 200, 20000),
(3, 'C', 'сверхскоростной', 100, 300, 30000),
(4, 'D', 'легкий', 125, 400, 40000),
(5, 'E', 'быстрейший', 150, 500, 50000);

--
-- Индексы сохранённых таблиц
--

--
-- Индексы таблицы `accelerator`
--
ALTER TABLE `accelerator`
  ADD PRIMARY KEY (`accelerator_id`);

--
-- Индексы таблицы `cartograph`
--
ALTER TABLE `cartograph`
  ADD PRIMARY KEY (`cartograph_id`);

--
-- Индексы таблицы `chinilka`
--
ALTER TABLE `chinilka`
  ADD PRIMARY KEY (`chinilka_id`);

--
-- Индексы таблицы `circulatory`
--
ALTER TABLE `circulatory`
  ADD PRIMARY KEY (`circulatory_id`);

--
-- Индексы таблицы `engine`
--
ALTER TABLE `engine`
  ADD PRIMARY KEY (`engine_id`);

--
-- Индексы таблицы `escadra`
--
ALTER TABLE `escadra`
  ADD PRIMARY KEY (`escadra_id`);

--
-- Индексы таблицы `eyes`
--
ALTER TABLE `eyes`
  ADD PRIMARY KEY (`eyes_id`);

--
-- Индексы таблицы `fuel_tank`
--
ALTER TABLE `fuel_tank`
  ADD PRIMARY KEY (`fuel_tank_id`);

--
-- Индексы таблицы `generator`
--
ALTER TABLE `generator`
  ADD PRIMARY KEY (`generator_id`);

--
-- Индексы таблицы `grab`
--
ALTER TABLE `grab`
  ADD PRIMARY KEY (`grab_id`);

--
-- Индексы таблицы `hearing`
--
ALTER TABLE `hearing`
  ADD PRIMARY KEY (`hearing_id`);

--
-- Индексы таблицы `help`
--
ALTER TABLE `help`
  ADD PRIMARY KEY (`help_id`);

--
-- Индексы таблицы `human_generator`
--
ALTER TABLE `human_generator`
  ADD PRIMARY KEY (`human_generator_id`);

--
-- Индексы таблицы `immunity`
--
ALTER TABLE `immunity`
  ADD PRIMARY KEY (`immunity_id`);

--
-- Индексы таблицы `improvement`
--
ALTER TABLE `improvement`
  ADD PRIMARY KEY (`improvement_id`);

--
-- Индексы таблицы `map`
--
ALTER TABLE `map`
  ADD PRIMARY KEY (`map_id`);

--
-- Индексы таблицы `muscle`
--
ALTER TABLE `muscle`
  ADD PRIMARY KEY (`mescle_id`);

--
-- Индексы таблицы `nerves`
--
ALTER TABLE `nerves`
  ADD PRIMARY KEY (`nerves_id`);

--
-- Индексы таблицы `news`
--
ALTER TABLE `news`
  ADD PRIMARY KEY (`news_id`);

--
-- Индексы таблицы `player`
--
ALTER TABLE `player`
  ADD PRIMARY KEY (`player_id`);

--
-- Индексы таблицы `protection`
--
ALTER TABLE `protection`
  ADD PRIMARY KEY (`protection_id`);

--
-- Индексы таблицы `race`
--
ALTER TABLE `race`
  ADD PRIMARY KEY (`race_id`);

--
-- Индексы таблицы `radar`
--
ALTER TABLE `radar`
  ADD PRIMARY KEY (`radar_id`);

--
-- Индексы таблицы `rank`
--
ALTER TABLE `rank`
  ADD PRIMARY KEY (`rank_id`);

--
-- Индексы таблицы `rating`
--
ALTER TABLE `rating`
  ADD PRIMARY KEY (`rating_id`);

--
-- Индексы таблицы `reproduction`
--
ALTER TABLE `reproduction`
  ADD PRIMARY KEY (`reproduction_id`);

--
-- Индексы таблицы `resource`
--
ALTER TABLE `resource`
  ADD PRIMARY KEY (`resource_id`);

--
-- Индексы таблицы `respirator`
--
ALTER TABLE `respirator`
  ADD PRIMARY KEY (`respirator_id`);

--
-- Индексы таблицы `reward`
--
ALTER TABLE `reward`
  ADD PRIMARY KEY (`reward_id`);

--
-- Индексы таблицы `scaner`
--
ALTER TABLE `scaner`
  ADD PRIMARY KEY (`scaner_id`);

--
-- Индексы таблицы `sceleton`
--
ALTER TABLE `sceleton`
  ADD PRIMARY KEY (`sceleton_id`);

--
-- Индексы таблицы `scent`
--
ALTER TABLE `scent`
  ADD PRIMARY KEY (`scent_id`);

--
-- Индексы таблицы `screen`
--
ALTER TABLE `screen`
  ADD PRIMARY KEY (`screen_id`);

--
-- Индексы таблицы `ship`
--
ALTER TABLE `ship`
  ADD PRIMARY KEY (`ship_id`);

--
-- Индексы таблицы `ship_body`
--
ALTER TABLE `ship_body`
  ADD PRIMARY KEY (`body_id`);

--
-- Индексы таблицы `spec`
--
ALTER TABLE `spec`
  ADD PRIMARY KEY (`spec_id`);

--
-- Индексы таблицы `taste`
--
ALTER TABLE `taste`
  ADD PRIMARY KEY (`taste_id`);

--
-- Индексы таблицы `weapons`
--
ALTER TABLE `weapons`
  ADD PRIMARY KEY (`weapons_id`);

--
-- Индексы таблицы `world`
--
ALTER TABLE `world`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `yotanet`
--
ALTER TABLE `yotanet`
  ADD PRIMARY KEY (`yotanet_id`);

--
-- AUTO_INCREMENT для сохранённых таблиц
--

--
-- AUTO_INCREMENT для таблицы `accelerator`
--
ALTER TABLE `accelerator`
  MODIFY `accelerator_id` int(10) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=8;
--
-- AUTO_INCREMENT для таблицы `cartograph`
--
ALTER TABLE `cartograph`
  MODIFY `cartograph_id` int(10) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=5;
--
-- AUTO_INCREMENT для таблицы `chinilka`
--
ALTER TABLE `chinilka`
  MODIFY `chinilka_id` int(10) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=7;
--
-- AUTO_INCREMENT для таблицы `circulatory`
--
ALTER TABLE `circulatory`
  MODIFY `circulatory_id` int(10) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT для таблицы `engine`
--
ALTER TABLE `engine`
  MODIFY `engine_id` int(10) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=6;
--
-- AUTO_INCREMENT для таблицы `escadra`
--
ALTER TABLE `escadra`
  MODIFY `escadra_id` int(10) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT для таблицы `eyes`
--
ALTER TABLE `eyes`
  MODIFY `eyes_id` int(10) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT для таблицы `fuel_tank`
--
ALTER TABLE `fuel_tank`
  MODIFY `fuel_tank_id` int(10) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=5;
--
-- AUTO_INCREMENT для таблицы `generator`
--
ALTER TABLE `generator`
  MODIFY `generator_id` int(10) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=5;
--
-- AUTO_INCREMENT для таблицы `grab`
--
ALTER TABLE `grab`
  MODIFY `grab_id` int(10) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=7;
--
-- AUTO_INCREMENT для таблицы `hearing`
--
ALTER TABLE `hearing`
  MODIFY `hearing_id` int(10) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT для таблицы `help`
--
ALTER TABLE `help`
  MODIFY `help_id` int(10) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT для таблицы `human_generator`
--
ALTER TABLE `human_generator`
  MODIFY `human_generator_id` int(10) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT для таблицы `immunity`
--
ALTER TABLE `immunity`
  MODIFY `immunity_id` int(10) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT для таблицы `improvement`
--
ALTER TABLE `improvement`
  MODIFY `improvement_id` int(10) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT для таблицы `map`
--
ALTER TABLE `map`
  MODIFY `map_id` int(10) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=2;
--
-- AUTO_INCREMENT для таблицы `muscle`
--
ALTER TABLE `muscle`
  MODIFY `mescle_id` int(10) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT для таблицы `nerves`
--
ALTER TABLE `nerves`
  MODIFY `nerves_id` int(10) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT для таблицы `news`
--
ALTER TABLE `news`
  MODIFY `news_id` int(10) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT для таблицы `player`
--
ALTER TABLE `player`
  MODIFY `player_id` int(10) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=2;
--
-- AUTO_INCREMENT для таблицы `protection`
--
ALTER TABLE `protection`
  MODIFY `protection_id` int(10) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=8;
--
-- AUTO_INCREMENT для таблицы `race`
--
ALTER TABLE `race`
  MODIFY `race_id` int(10) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=8;
--
-- AUTO_INCREMENT для таблицы `radar`
--
ALTER TABLE `radar`
  MODIFY `radar_id` int(10) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=6;
--
-- AUTO_INCREMENT для таблицы `rank`
--
ALTER TABLE `rank`
  MODIFY `rank_id` int(10) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT для таблицы `rating`
--
ALTER TABLE `rating`
  MODIFY `rating_id` int(10) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT для таблицы `reproduction`
--
ALTER TABLE `reproduction`
  MODIFY `reproduction_id` int(10) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT для таблицы `resource`
--
ALTER TABLE `resource`
  MODIFY `resource_id` int(10) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT для таблицы `respirator`
--
ALTER TABLE `respirator`
  MODIFY `respirator_id` int(10) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT для таблицы `reward`
--
ALTER TABLE `reward`
  MODIFY `reward_id` int(10) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT для таблицы `scaner`
--
ALTER TABLE `scaner`
  MODIFY `scaner_id` int(10) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=6;
--
-- AUTO_INCREMENT для таблицы `sceleton`
--
ALTER TABLE `sceleton`
  MODIFY `sceleton_id` int(10) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT для таблицы `scent`
--
ALTER TABLE `scent`
  MODIFY `scent_id` int(10) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT для таблицы `screen`
--
ALTER TABLE `screen`
  MODIFY `screen_id` int(10) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT для таблицы `ship`
--
ALTER TABLE `ship`
  MODIFY `ship_id` int(10) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT для таблицы `ship_body`
--
ALTER TABLE `ship_body`
  MODIFY `body_id` int(10) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=6;
--
-- AUTO_INCREMENT для таблицы `spec`
--
ALTER TABLE `spec`
  MODIFY `spec_id` int(10) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=7;
--
-- AUTO_INCREMENT для таблицы `taste`
--
ALTER TABLE `taste`
  MODIFY `taste_id` int(10) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT для таблицы `weapons`
--
ALTER TABLE `weapons`
  MODIFY `weapons_id` int(10) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=8;
--
-- AUTO_INCREMENT для таблицы `world`
--
ALTER TABLE `world`
  MODIFY `id` int(10) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=2;
--
-- AUTO_INCREMENT для таблицы `yotanet`
--
ALTER TABLE `yotanet`
  MODIFY `yotanet_id` int(10) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=6;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
