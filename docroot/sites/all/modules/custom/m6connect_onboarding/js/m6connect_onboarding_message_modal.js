Drupal.theme.prototype.OnboardingMessagePopup = function () {
  var html = '';
  var modalClass ='';
  if(Drupal.CTools.Modal.currentSettings.hasOwnProperty('modalClass') && Drupal.CTools.Modal.currentSettings.modalClass){
    modalClass =  ' '+Drupal.CTools.Modal.currentSettings.modalClass;
  }
  html += '<div id="ctools-modal" class="popups-box">';
  html += '  <div class="ctools-modal-content modal-forms-modal-content onboarding-message-modal-container'+modalClass+'">';
  html += '    <div class="popups-container">';
  html += '      <div class="modal-header popups-title" style="display:none;">';
  html += '        <span class="popups-close close">' + Drupal.CTools.Modal.currentSettings.closeText + '</span>';
  html += '        <div class="clear-block"></div>';
  html += '      </div>';
  html += '      <div class="modal-scroll">';
  html += '        <div class="custom-modal-title text-center"><span id="modal-title" class="modal-title"></span></div>';
  html += '        <div id="modal-content" class="modal-content popups-body"></div>';
  html += '      </div>';
  html += '    </div>';
  html += '  </div>';
  html += '</div>';

  return html;
}



Drupal.theme.prototype.OnboardingM6IDPopup = function () {
  var html = '';
  var modalClass ='';
  if(Drupal.CTools.Modal.currentSettings.hasOwnProperty('modalClass') && Drupal.CTools.Modal.currentSettings.modalClass){
    modalClass =  ' '+Drupal.CTools.Modal.currentSettings.modalClass;
  }
  html += '<div id="ctools-modal" class="popups-box">';
  html += '  <div class="ctools-modal-content modal-forms-modal-content onboarding-message-modal-container'+modalClass+'">';
  html += '    <div class="popups-container">';
  html += '      <div class="modal-header popups-title" style="display:none;">';
  //html += '        <span class="popups-close close">' + Drupal.CTools.Modal.currentSettings.closeText + '</span>';
  html += '        <div class="clear-block"></div>';
  html += '      </div>';
  html += '      <div class="modal-scroll">';
  html += '        <div class="m6id-popup-close">';
  html += '          <span class="m6id-popup-print-icon"><i class="fa fa-print" aria-hidden="true"></i></span>';
  html += '          <span class="popups-close close">' + Drupal.CTools.Modal.currentSettings.closeText + '</span>';
  html += '        </div>';
  html += '        <div id="modal-content" class="modal-content popups-body"></div>';
  html += '      </div>';
  html += '    </div>';
  html += '  </div>';
  html += '</div>';

  return html;
}