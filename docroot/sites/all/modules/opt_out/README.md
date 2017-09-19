The opt out module provides a checkbox on the user's profile page.

When checked, most emails will not be sent to the user. An exception is made
for certain emails, so that password recovery emails and the like can still
be sent if needed.

You can modify which emails ignore the opt out setting by setting
a variable in your settings.php:

    $conf['opt_out_send_anyway'] = array('user', 'system:action_send_email');

If the key doesn't contain a :, all emails from that module will pass through.
If it does contain a :, only emails with that module and key will pass through.