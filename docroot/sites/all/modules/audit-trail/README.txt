
-- SUMMARY --

The Audit Trail features logging either form submissions or changes made to a
form. The forms to be tracked are specified by providing a regexp pattern that
matches either the form id or the path the form appears on. It is also possible
to add tracking to a form via track management links if the module is configured
to show them.

For a full description of the module, visit the project page:
  http://drupal.org/project/audit-trail

To submit bug reports and feature suggestions, or to track changes:
  http://drupal.org/project/issues/audit-trail


-- DESCRIPTION --

Forms can be tracked either for changes or submissions. The submission tracking
is straightforward, the contents of $form_state['values'] gets logged. The
change tracking compares each form element's #default_value and #value fields
to find changes to be logged.

The module supports writing log entries to a custom file or watchdog. The logs
will contain context and the actual logs. By default the context will contain
the time of submission, the submitting user's uid, the form's id and the form
element that triggered the submission. In case of form submission tracking the
log will contain the serialized array of the $form_state['values']. In case of
form change tracking the logs will contain the path of the field being changed
and before / after values. Checkboxes, multiple select lists and multiple
tableselect elements will list items which were selected but got unselected and
vice versa. The following example shows that checkbox_one started as checked and
got unchecked while checkbox_three went from unchecked to checked.
a:2:{s:12:"checkbox_one";i:1;s:14:"checkbox_three";i:0;}
a:2:{s:12:"checkbox_one";i:0;s:14:"checkbox_three";i:1;}

Password and password_confirm field values are being rewritten with 'Hidden'
text to hide sensitive information. If there are other similar sensitive fields
to be blanked out or rewritten that can be done by implementing
 * hook_audit_trail_form_change_log_alter
 * hook_audit_trail_form_submit_log_alter
and rewriting or unsetting fields as necessary.

These hooks can also be used to write the logs to a custom storage. To stop the
module from writing out anything just empty the variables in the hooks.


-- REQUIREMENTS --

None.


-- INSTALLATION --

* Install as usual, for further information see
http://drupal.org/documentation/install/modules-themes/modules-7


-- CONFIGURATION --

* Configure user permissions on admin/people/permissions:

  - Administer audit trail

    Allows configuring the module. This permission is also needed to be able to
    see the form tracking management links when they are enabled.

* Configure the module on admin/config/development/audit-trail.


-- CONTACT --

Current maintainers:
* Kevin Hankens - http://drupal.org/user/78090
* Balazs Nagykekesi (nagba) - http://drupal.org/user/21231
* Eduardo Garcia (-enzo-) - http://drupal.org/user/294937

This project has been sponsored by:
* Acquia
  Commercially Supported Drupal. Visit http://acquia.com for more information.
