-- phpMyAdmin SQL Dump
-- version 3.4.10.1
-- http://www.phpmyadmin.net
--
-- 主机: localhost
-- 生成日期: 2014 年 05 月 22 日 09:59
-- 服务器版本: 5.5.20
-- PHP 版本: 5.3.10

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- 数据库: `bagra`
--

-- --------------------------------------------------------

--
-- 表的结构 `bag_aglist`
--

CREATE TABLE IF NOT EXISTS `bag_aglist` (
  `ag_id` int(11) NOT NULL AUTO_INCREMENT,
  `ag_name` varchar(128) NOT NULL,
  `ag_discription` varchar(256) NOT NULL,
  `ag_gendate` datetime NOT NULL,
  `ag_group` int(11) NOT NULL,
  `ag_status` int(11) NOT NULL,
  PRIMARY KEY (`ag_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=4 ;

--
-- 转存表中的数据 `bag_aglist`
--

INSERT INTO `bag_aglist` (`ag_id`, `ag_name`, `ag_discription`, `ag_gendate`, `ag_group`, `ag_status`) VALUES
(1, 'First Day Gen', 'This is the CIA internal system be sure that you have got the permission and have been granted!', '2014-04-28 09:24:36', 2, 1),
(2, 'Risk Problem ', 'To be Continue.\nRisk level is partly good!', '2014-04-30 13:12:32', 2, 3),
(3, 'Commit For partly', 'Please call me maybe', '2014-05-01 14:19:40', 2, 2);

-- --------------------------------------------------------

--
-- 表的结构 `bag_project`
--

CREATE TABLE IF NOT EXISTS `bag_project` (
  `project_id` int(11) NOT NULL AUTO_INCREMENT,
  `project_name` varchar(128) NOT NULL,
  `project_rank` int(11) NOT NULL,
  PRIMARY KEY (`project_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=8 ;

--
-- 转存表中的数据 `bag_project`
--

INSERT INTO `bag_project` (`project_id`, `project_name`, `project_rank`) VALUES
(1, 'NASA Inner System of Spacecraft Department', 4),
(2, 'CIA Central React Department', 3),
(3, 'National Security College of Habin Engineer University', 2),
(4, 'CMU University', 1),
(7, 'Harbin', 1);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
