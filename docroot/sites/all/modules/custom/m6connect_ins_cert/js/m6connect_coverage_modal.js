Drupal.theme.prototype.AssignCoveragePopup = function () {
  var html = '';
  html += '<div id="ctools-modal" class="popups-box">';
  html += '  <div class="ctools-modal-content modal-forms-modal-content assign-dashboard-popup-container">';
  html += '    <div class="popups-container">';
  html += '      <div class="modal-header popups-title" style="display:none;">';
  //html += '        <span id="modal-title" class="modal-title"></span>';
  html += '        <span class="popups-close close">' + Drupal.CTools.Modal.currentSettings.closeText + '</span>';
  html += '        <div class="clear-block"></div>';
  html += '      </div>';
  html += '      <div class="modal-scroll"><div class="cust-assign-dashboard-title"><span id="modal-title" class="modal-title"></span></div><div id="modal-content" class="modal-content popups-body"></div></div>';
  html += '    </div>';
  html += '  </div>';
  html += '</div>';

  return html;
}