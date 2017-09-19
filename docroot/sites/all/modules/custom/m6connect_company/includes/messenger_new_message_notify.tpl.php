<div style="background:#eaeef1;float:left;width:100%;min-height:100%;padding: 80px 0;">
  <div class="m6messenger-template" style="width: 600px;margin: 0 auto;">
    <div style="padding:10px;background:#f5f7f9;border-bottom:1px solid #ccc;float:left;width: 580px;">
      <div style="float:left;width:20%"><?php print $messenger['SiteLogo']; ?></div>
      <div style="float:left;width:80%;text-align:right"> <span style="padding-right:10px;line-height:50px;display: inline-block;vertical-align: middle;"><strong><?php print $messenger['ReceiverUserName']; ?></strong></span><span style="height:50px;width:50px;line-height:50px;display: inline-block;vertical-align: top;"><?php print $messenger['ReceiverUserLogo']; ?></span> </div>
    </div>
    <div style="float:left;width: 590px;background:#fff;padding:0 5px;">
      <h2 style="margin:0;font-weight: 400;">You have an unread message from <strong><?php print $messenger['SenderUserName']; ?></strong></h2>
    </div>
    <div style="float:left;width: 560px;padding:10px 20px;background:#fff;">
      <div style="float:left;width: 18%;"><?php print $messenger['SenderUserLogo']; ?></div>
      <div style="float:left;width:80%;line-height:80px;"><strong><?php print $messenger['SenderUserName']; ?></strong></div>
    </div>
    <div style="float:left;width: 560px;padding:10px 20px;background:#fff;">
      <div style="padding:10px;background:#f1f1f1;float:left;width: 540px;margin-bottom:20px;">
        <!--<div style="margin-bottom:10px;"><?php //print $messenger['ReceiverUserName']; ?>,</div>-->
        <div><?php print $messenger['MessageText']; ?> </div>
      </div>
      <div style="float:left;width:100%;margin-bottom: 10px;"> <?php print $messenger['ReplyLink']; ?> </div>
    </div>
  </div>
</div>
