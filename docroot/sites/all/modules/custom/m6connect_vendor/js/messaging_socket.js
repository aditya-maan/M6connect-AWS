var socket_messaging = '';
(function ($) {
  $(document).ready(function($) {
    socket_messaging = io.connect('https://www.m6cliq.info/');

    var username = Drupal.settings.m6connect_prochat.username;
    var myobj = { "username": username };
    socket_messaging.emit("usernameSubmit_broadcast", JSON.stringify(myobj));
    socket_messaging.on('connectionstatus', function(data) {
      if (data === '0') {
        socket_messaging.emit("usernameSubmit_broadcast", JSON.stringify(myobj));
      }
    });

    socket_messaging.on('gettingMessageService', function(data) {
      if ($('.vendor-manager-messaging-form').length > 0) {
        refreshVendorMessageContent();
      }
      if ($('.user_messaging_thread_form').length > 0) {
        refreshMessageContent();
      }
      // socket_messaging.emit("usernameSubmit_broadcast", JSON.stringify(myobj));
    });

    socket_messaging.on('emitterOfSeen', function(fromusername, mid) {
      updateSeenListMessaging(fromusername, mid);
    });

  });
}(jQuery));