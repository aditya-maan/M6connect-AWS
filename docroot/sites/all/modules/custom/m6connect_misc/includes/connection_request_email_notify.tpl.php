<div style="background:#eaeef1;float:left;width:100%;min-height:100%;padding:80px 0">
  <div class="template" style="width:600px;margin:0 auto">
    <div style="padding:10px;background:#f5f7f9;border-bottom:1px solid #ccc;float:left;width:580px">
      <div style="float:left;width:20%"><img style="width:50px;height:50px" src="<?php print $connctionUserDetail['SiteLogoUrl']; ?>" alt="" class="CToWUd"></div>
      <div style="float:left;width:80%;text-align:right"> <span style="padding-right:10px;line-height:50px;display:inline-block;vertical-align:middle"><strong><?php print $connctionUserDetail['ReceiverName']; ?></strong></span><span style="height:50px;width:50px;line-height:50px;display:inline-block;vertical-align:top"><img style="vertical-align:top; border-radius:50%;" src="<?php print $connctionUserDetail['ReceiverPic']; ?>" width="50" height="50" alt="" class="CToWUd"></span> </div>
    </div>
    <div style="float:left;width:560px;padding:10px 20px;background:#fff">
      <div style="float:left;width:100%; margin:0 0 15px 0;">
        <h3 style="margin:0;font-weight:400"><?php print $connctionUserDetail['Message']; ?></h3>
      </div>
      <div style="float:left;width:100%; margin:0 0 15px 0;">
        <div style="float:left;width:18%"><img style="line-height:80px; border-radius:50%;" src="<?php print $connctionUserDetail['SenderPic']; ?>" width="80" height="80" alt="" class="CToWUd"></div>
        <div style="float:left;width:80%;line-height:normal;">
          <div><strong><?php print $connctionUserDetail['SenderName']; ?></strong></div>
          <div><?php print $connctionUserDetail['SenderDesig']; ?></div>
          <!--<div>Location Area</div>--> 
        </div>
      </div>
      <div style="float:left;width:100%;"> <a href="<?php print $connctionUserDetail['SenderToMessageLink']; ?>" style="background:#FFF; padding:8px 20px; border-radius:3px; border:1px solid #333; margin:0 10px 0 0; display:inline-block; vertical-align:top; color:#333; text-decoration:none;">Message</a> <a href="<?php print $connctionUserDetail['SenderProfileLink']; ?>" style="background:#265a7f; padding:8px 20px; border-radius:3px; border:1px solid #265a7f; display:inline-block; vertical-align:top; color:#FFF; text-decoration:none;">View Profile</a> </div>
    </div>
    <?php if(!empty($peopleYouMayKnowDetail)) { ?>
    <div style="float:left;width:520px;padding:30px 40px;background:#F5F7F9">
      <div style="float:left; width:100%;margin:0 0 15px 0;">
        <h2 style="margin:0; text-align:center; font-weight:400;">People You May Know</h2>
      </div>
      <?php foreach($peopleYouMayKnowDetail as $delta => $peopleDetail) { ?>
      <div style="float:left;width:100%; margin:0 0 15px 0;">
        <div style="float:left;width:18%"><img style="line-height:50px; border-radius:50%;" src="<?php print $peopleDetail['user_pic']; ?>" width="50" height="50" alt="" class="CToWUd"></div>
        <div style="float:left;width:80%;line-height:normal;">
          <div><strong><?php print $peopleDetail['user_name']; ?></strong></div>
          <div><?php print $peopleDetail['user_desi']; ?></div>
          <div><a href="<?php print $peopleDetail['connect_uri']; ?>" style="text-decoration:none;"><strong>+ Connect</strong></a></div>
        </div>
      </div>
      <?php } ?>
      <!--<div style="float:left;width:100%;margin-bottom:15px; text-align:center;"> <a href="" style="display:inline-block; background:#265a7f;padding:8px 20px;color:#fff;border:none; text-decoration:none;" target="_blank">See More</a> </div>--> 
    </div>
    <?php } ?>
  </div>
</div>
