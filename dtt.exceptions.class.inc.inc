<?php

class GeneralException extends Exception {
  public function __construct($error, $errno) {
    parent::__construct($error, $errno);
  }
}

class BadRequestException extends Exception {
  public function __construct() {
    $errno = 400;
    $error = "Bad request:  Badly formatted request.";
    parent::__construct($error, $errno);
  }
}

class NotFoundException extends Exception {
  public function __construct() {
    $errno = 404;
    $error = "Not Found: The query you asked for did not return any data.";
    parent::__construct($error, $errno);
  }  
}

class UnavailableException extends Exception {
  public function __construct() {
    $errno = 503;
    $error = "Service Unavailable: your available credits ran out (reset every 24 hours);";
    parent::__construct($error, $errno);
  }  
}