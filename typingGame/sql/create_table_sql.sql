-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

-- -----------------------------------------------------
-- Schema TypingGame
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema TypingGame
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `TypingGame` DEFAULT CHARACTER SET utf8 ;
USE `TypingGame` ;

-- -----------------------------------------------------
-- Table `TypingGame`.`profile_images`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `TypingGame`.`profile_images` (
  `img_id` VARCHAR(15) NOT NULL,
  `img_path` VARCHAR(100) NULL,
  PRIMARY KEY (`img_id`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `TypingGame`.`users`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `TypingGame`.`users` (
  `user_id` VARCHAR(12) NOT NULL,
  `password` VARCHAR(15) NULL,
  `nickname` VARCHAR(36) NULL,
  `reg_date` DATETIME NULL,
  `profile_images_img_id` VARCHAR(15) NOT NULL,
  PRIMARY KEY (`user_id`),
  INDEX `fk_users_profile_images_idx` (`profile_images_img_id` ASC) VISIBLE,
  CONSTRAINT `fk_users_profile_images`
    FOREIGN KEY (`profile_images_img_id`)
    REFERENCES `TypingGame`.`profile_images` (`img_id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `TypingGame`.`user_files`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `TypingGame`.`user_files` (
  `file_id` INT NOT NULL,
  `user_id` VARCHAR(12) NULL,
  `file_title` VARCHAR(45) NULL,
  `file_path` VARCHAR(100) NULL,
  `file_extension` VARCHAR(45) NULL,
  `upload_date` DATETIME NULL,
  `language` VARCHAR(10) NULL,
  PRIMARY KEY (`file_id`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `TypingGame`.`text_file_ko`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `TypingGame`.`text_file_ko` (
  `file_id` VARCHAR(10) NOT NULL,
  `file_path` VARCHAR(100) NULL,
  PRIMARY KEY (`file_id`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `TypingGame`.`code_files`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `TypingGame`.`code_files` (
  `file_id` VARCHAR(10) NOT NULL,
  `file_path` VARCHAR(100) NULL,
  `language` VARCHAR(10) NULL,
  PRIMARY KEY (`file_id`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `TypingGame`.`text_file_en`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `TypingGame`.`text_file_en` (
  `file_id` VARCHAR(10) NOT NULL,
  `file_path` VARCHAR(100) NULL,
  PRIMARY KEY (`file_id`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `TypingGame`.`rankings`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `TypingGame`.`rankings` (
  `users_user_id` VARCHAR(12) NOT NULL,
  `point` INT NULL,
  PRIMARY KEY (`users_user_id`),
  CONSTRAINT `fk_rankings_users1`
    FOREIGN KEY (`users_user_id`)
    REFERENCES `TypingGame`.`users` (`user_id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `TypingGame`.`user_stats`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `TypingGame`.`user_stats` (
  `user_id` VARCHAR(12) NOT NULL,
  `avg_speed` INT NULL,
  `avg_accuracy` INT NULL,
  `total_games` INT NULL,
  `total_wins` INT NULL,
  `total_play_time` INT NULL,
  PRIMARY KEY (`user_id`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `TypingGame`.`game_logs`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `TypingGame`.`game_logs` (
  `log_id` INT NOT NULL AUTO_INCREMENT,
  `session_id` VARCHAR(45) NULL,
  `log_date` DATETIME NULL,
  `play_time` INT NULL,
  `log_speed` INT NULL,
  `log_accuracy` INT NULL,
  `result` INT NULL,
  `user_id` VARCHAR(12) NOT NULL,
  `is_match` TINYINT NULL,
  PRIMARY KEY (`log_id`),
  INDEX `fk_game_logs_users1_idx` (`user_id` ASC) VISIBLE,
  CONSTRAINT `fk_game_logs_users1`
    FOREIGN KEY (`user_id`)
    REFERENCES `TypingGame`.`users` (`user_id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `TypingGame`.`match_logs`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `TypingGame`.`match_logs` (
  `match_log_id` INT NOT NULL,
  `winner_id` VARCHAR(12) NOT NULL,
  `loser_id` VARCHAR(12) NOT NULL,
  `match_date` DATETIME NULL,
  `match_duration` INT NULL,
  `winner_point` INT NULL,
  `loser_point` INT NULL,
  INDEX `fk_match_logs_users1_idx` (`winner_id` ASC) VISIBLE,
  INDEX `fk_match_logs_users2_idx` (`loser_id` ASC) VISIBLE,
  PRIMARY KEY (`match_log_id`),
  CONSTRAINT `fk_match_logs_users1`
    FOREIGN KEY (`winner_id`)
    REFERENCES `TypingGame`.`users` (`user_id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_match_logs_users2`
    FOREIGN KEY (`loser_id`)
    REFERENCES `TypingGame`.`users` (`user_id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_match_logs_game_logs1`
    FOREIGN KEY (`match_log_id`)
    REFERENCES `TypingGame`.`game_logs` (`log_id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
