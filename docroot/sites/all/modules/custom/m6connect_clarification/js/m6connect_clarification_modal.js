Drupal.theme.prototype.custom_clarification_msg_theme= function () {
  var html = '';
  html += '<div id="ctools-modal" class="popups-box custom-clarification-msg-popup">';
  html += ' <div class="ctools-modal-content my-popup ">';
  html += '<span class="popups-close close clarification-msg-close">' + Drupal.CTools.Modal.currentSettings.closeText + '</span>';
  html += ' <div class="modal-msg"></div>';
  html += ' <div class="modal-scroll"><div id="modal-content" class="modal-content popups-body"></div></div>';
  html += ' </div>';
  html += '</div>';
  return html;
}

Drupal.theme.prototype.ClarificationMsgPopup = function () {
  var html = '';

  html += '<div id="ctools-modal" class="popups-box">';
  html += '  <div class="ctools-modal-content modal-forms-modal-content clarification-msg-popup-container">';
  html += '    <div class="popups-container">';
  html += '      <div class="modal-header popups-title" style="display:none;">';
  html += '        <span id="modal-title" class="modal-title"></span>';
  html += '        <span class="popups-close close">' + Drupal.CTools.Modal.currentSettings.closeText + '</span>';
  html += '        <div class="clear-block"></div>';
  html += '      </div>';
  html += '      <div class="modal-scroll"><div id="modal-content" class="modal-content popups-body"></div></div>';
  html += '    </div>';
  html += '  </div>';
  html += '</div>';

  return html;
}

Drupal.theme.prototype.ClarificationFormsPopup = function () {
  var html = '';

  html += '<div id="ctools-modal" class="popups-box">';
  html += '  <div class="ctools-modal-content modal-forms-modal-content clarification-msg-form-popup">';
  html += '    <div class="popups-container">';
  html += '      <div class="modal-header popups-title" style="display:none;">';
  html += '        <span id="modal-title" class="modal-title"></span>';
  html += '        <span class="popups-close close">' + Drupal.CTools.Modal.currentSettings.closeText + '</span>';
  html += '        <div class="clear-block"></div>';
  html += '      </div>';
  html += '      <div class="modal-scroll"><div id="modal-content" class="modal-content popups-body"></div></div>';
  html += '    </div>';
  html += '  </div>';
  html += '</div>';

  return html;
}