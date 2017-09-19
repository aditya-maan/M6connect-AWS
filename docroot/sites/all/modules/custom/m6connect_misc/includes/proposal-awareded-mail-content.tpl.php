<div>
  <div id="page_1" style="color: #3E3E3F;font-size: 16px;text-align: center;width: 570px;height: 100%;margin: 0 auto; padding:15px;background: url(<?php print $replace['[Proposal:bgImagePath]']; ?>) no-repeat;">
    <div class="header" style="height:120px;">
    </div>
    <div class="content" style="height:420px;">
      <div class="awarding" style="font-size: 30px;line-height:30px;height:70px;margin:0 0 10px 0;"><?php print $replace['[Proposal:RFPCompanyName]']; ?> has formally selected:</div>
      <div class="awarding-heading" style="color: #1E608D;font-size: 36px;line-height:36px;height:75px;margin:0 0 10px 0;"><?php print $replace['[Proposal:SenderCompanyName]']; ?><?php if($replace['[Proposal:Type]']=='RFP') { ?><div><strong style="color: #1E608D; font-size:20px;"><?php print $replace['[Proposal:BidderFeedBackName]']; ?></stong></div><?php } ?></div>
      <div class="hdr" style="font-size:20px;height:90px;">For the <strong style="color: #1E608D;"><?php print $replace['[Proposal:Name]']; ?></strong> <span><?php print $replace['[Proposal:Type]']; ?></span><br />
        <?php if($replace['[Proposal:Type]']=='RFP') { ?>
          <?php if(!empty($replace['[Proposal:RFPCityState]'])){
			  print $replace['[Proposal:RFPCityState]'].'<br />'; 
		  } ?>
        <?php } else{?>
          <?php print $replace['[Proposal:RFPCityState]']; ?><br />
        <?php } ?>
        Date: <?php print date('m-d-Y'); ?></div>
      <div class="m6connect" style="font-style:italic;height:80px;margin:0 0 10px 0;line-height:18px;">M6Connect is proud to present this award on behalf of <?php print $replace['[Proposal:RFPCompanyName]']; ?>.<br />
        M6Connect is excited to be the leader at improving the project pursuit process.<br />
        Thank you for contributing to our vision to become the world’s leader in the<br />
        execution of business initiatives.</div>
      <div class="connect-logo"><a href="https://www.m6connect.com" title="m6connect.com" style="color: #1E608D;text-decoration: none;"><img src="<?php print $replace['[Proposal:m6LogoPath]']; ?>" alt="logo" width="150" /></a></div>
    </div>
    <div class="footer" style="padding:40px 0 0 0;">
    </div>
  </div>
</div>