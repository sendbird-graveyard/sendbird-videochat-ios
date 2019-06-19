Pod::Spec.new do |s|
  s.name         = "SendBirdVideoChat"
  s.version      = "0.9.1"
  s.summary      = "SendBird VideoChat Framework"
  s.description  = "SendBird VideoChat provides the video/audio call."
  s.homepage     = "https://sendbird.com"
  s.license      = { :type => 'Commercial' }
  s.authors      = { "Jed Gyeong" => "jed.gyeong@sendbird.com", "Young Hwang" => "young.hwang@sendbird.com" }
  s.source       = { :git => "https://github.com/sendbird/sendbird-videochat-ios.git", :tag => "v#{s.version}" }
  s.requires_arc = true
  s.platform = :ios, "9.0"
  s.documentation_url = 'https://docs.sendbird.com/'
  s.vendored_frameworks = 'SendBirdVideoChat.framework'
  s.dependency 'SendBirdSDK', '>= 3.0.133'
  s.library = 'z'
end
