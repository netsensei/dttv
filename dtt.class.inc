<?php

class DTT {
  
  // API version
  private $version = "1.0";
  
  /**
   * Returns the latest episode of a show.
   * 
   * @param type $show_name
   * @param type $jsonp
   * @return string A json formatted object
   */
  public function episode_get_latest($show_name) {
    $response = $this->query('episode.getLatest', array('show_name' => $show_name));
    return json_decode($response, TRUE);
  }

  /**
   * Normalizes a TV episode filename, you can use it to rename your files.
   * 
   * @param type $file_name
   * @return type 
   */
  public function misc_get_clean_file_name($file_name) { 
    return $this->query('misc.getCleanFileName', array('filename' => $file_name));
  }

  /**
   * Returns the episodes of a show. Contains episode numbers and what qualities (hd/720/1080) are available.
   * 
   * @param type $show_name
   * @param type $page
   * @return type 
   */
  public function show_get_episodes($show_name, $page = 0) { 
    $response = $this->query('show.getEpisodes', array('show_name' => $show_name, 'page' => $page));
    return json_decode($response);
  }
  
  /**
   * Gives back information about a show.
   * 
   * @param type $show_name
   * @return type 
   */
  public function show_get_info($show_name) { 
    $response = $this->query('show.getInfo', array('show_name' => $show_name));
    return json_decode($response);
  }
  
  /**
   * Returns the show objects of new series.
   * 
   * @param type $strict
   * @param type $max_age_hours
   * @param type $max_items
   * @param type $sort
   * @return type 
   */
  public function shows_get_new($strict = 'no', $max_age_hours = NULL, $max_items = 6, $sort = 'age') { 
    $arguments = array(
      'strict' => $strict,
      'max_items' => $max_items,
      'sort' => $sort,
    );
    
    if (!is_null($max_age_hours)) {
      $arguments['max_age_hours'] = $max_age_hours;
    }
    
    $response = $this->query('shows.getNew', $arguments);
    return json_decode($response);
  }
  
  /**
   * Returns the show objects of the most popular shows in the last 3 days.
   * 
   * @param type $max_items
   * @return type 
   */
  public function shows_get_popular($max_items = 6) {
    $response = $this->query('shows.getPopular', array('max_items' => $max_items));
    return json_decode($response);
  }
  
  /**
   * Returns the show objects of returning series in newest first order.
   * 
   * @param type $max_items
   * @return type 
   */
  public function shows_get_returning($max_items = 6) { 
    $response = $this->query('shows.getReturning', array('max_items' => $max_items));
    return json_decode($response);
  }
  
  /**
   * Searches for a show.
   * 
   * @param type $query
   * @param type $page
   * @return type 
   */
  public function shows_search($query, $page = 0) { 
    $response = $this->query('shows.search', array('query' => $query, 'page' => $page));
    return json_decode($response);
  }
  
  /**
   * Returns the torrent information (download link, seeds, peers, number of files) of an episode.
   * 
   * This returns a single torrent info object of the requested quality. If you want to get the best 
   * torrents for every available quality (HD, 720, 1080), you can use torrent.getInfos. 
   * If you need all torrents of an episode, you can use torrent.getInfosAll.
   * 
   * @param type $show_name
   * @param type $episode_num
   * @param type $quality
   * @param type $fallback
   * @return type 
   */
  public function torrent_get_info($show_name, $episode_num, $quality = 'hd', $fallback = 'no') { 
    $arguments = array(
      'show_name' => $show_name,
      'episode_num' => $episode_num,
      'quality' => $quality,
      'fallback' => $fallback,
    );
    $response = $this->query('torrent.getInfo', $arguments);
    return json_decode($response);
  }
  
  /**
   * Returns the torrent information (download link, seeds, peers, number of files) 
   * of an episode for all the available qualities.
   * 
   * @param type $show_name
   * @param type $episode_num
   * @return type 
   */
  public function torrent_get_infos($show_name, $episode_num) {
    $response = $this->query('torrent.getInfos', array('show_name' => $show_name, 'episode_num' => $episode_num));
    return json_decode($response);    
  }
  
  /**
   * Returns torrent information on all the torrents of a given episode.
   * 
   * @param type $show_name
   * @param type $episode_num
   * @return type 
   */
  public function torrent_get_infos_all($show_name, $episode_num) {
    $response = $this->query('torrent.getInfosAll', array('show_name' => $show_name, 'episode_num' => $episode_num));
    return json_decode($response);        
  }

  /**
   * Returns the torrent information (download link, seeds, peers, number of files) of the latest episode of a show.
   * 
   * @param type $show_name
   * @param type $quality
   * @param type $fallback
   * @param type $just_link
   * @return type 
   */
  public function torrent_get_latest($show_name, $quality = 'hd', $fallback = 'no', $just_link = 'no') {
    $arguments = array(
      'show_name' => $show_name,
      'quality' => $quality,
      'fallback' => $fallback,
      'just_link' => $just_link,
    );    
    $response = $this->query('torrent.getLatest', $arguments);

    if ($just_link == 'no') {
      $response = json_decode($response);
    }

    return $response;
  }
  
  /**
   * Queries the API
   * 
   * @param type $call
   *   The API call method
   * @param type $arguments 
   *   The arguments that the API call accepts
   */
  private function query($call, $arguments) {
    $host = 'http://api.dailytvtorrents.org';
    $path = '/' . $this->version . '/' . $call;
    $query = http_build_query($arguments);
    $response = FALSE;
    $http_code = 200;
    
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_URL, $host . $path . '?' . $query);
    curl_setopt($ch, CURLOPT_TIMEOUT, '5');
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);

    $response = trim(curl_exec($ch));

    $err_num = curl_errno($ch);
    $err_msg = curl_error($ch);
    $http_code = curl_getinfo($ch, CURLINFO_HTTP_CODE);

    curl_close($ch);    

    if ($err_num !== CURLE_OK) {
      throw new GeneralException($err_msg, $err_num);
    }
    
    switch ($http_code) {
      case 400 :
        throw new BadRequestException();
        break;
      case 404 :
        throw new NotFoundException();
        break;
      case 503 :
        throw new UnavailableException();
        break;
    }
    
    return $response;
  }
}