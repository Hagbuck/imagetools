
function toggleNotice() {
	var notice = document.getElementById('centralNotice');
	if (!wgNoticeToggleState) {
		notice.className = notice.className.replace('collapsed', 'expanded');
		toggleNoticeCookie('0');
	} else {
		notice.className = notice.className.replace('expanded', 'collapsed');
		toggleNoticeCookie('1');
	}
	wgNoticeToggleState = !wgNoticeToggleState;
}
function toggleNoticeStyle(elems, display) {
	if(elems)
		for(var i=0;i<elems.length;i++)
			elems[i].style.display = display;
}
function toggleNoticeCookie(state) {
	var e = new Date();
	e.setTime( e.getTime() + (7*24*60*60*1000) ); // one week
	var work='hidesnmessage='+state+'; expires=' + e.toGMTString() + '; path=/';
	document.cookie = work;
}
function pickTemplate(templates, weights) {
	var weightedTemplates = new Array();
	var currentTemplate = 0;
	var totalWeight = 0;

	if (templates.length == 0)
		return '';

	while (currentTemplate < templates.length) {
		totalWeight += weights[currentTemplate];
		for (i=0; i<weights[currentTemplate]; i++) {
			weightedTemplates[weightedTemplates.length] = templates[currentTemplate];
		}
		currentTemplate++;
	}
	
	if (totalWeight == 0)
		return '';

	var randomnumber=Math.floor(Math.random()*totalWeight);
	return weightedTemplates[randomnumber];
}


var wgNoticeToggleState = (document.cookie.indexOf('hidesnmessage=1')==-1);
document.writeln("\x3cstyle type=\"text/css\"\x3e\n#centralNotice .siteNoticeSmall{display:none;}\n#centralNotice .siteNoticeSmallAnon{display:none;}\n#centralNotice .siteNoticeSmallUser{display:none;}\n#centralNotice.collapsed .siteNoticeBig{display:none;}\n#centralNotice.collapsed .siteNoticeSmall{display:block;}\n#centralNotice.collapsed .siteNoticeSmallUser{display:block;}\n#centralNotice.collapsed .siteNoticeSmallAnon{display:block;}\n#centralNotice.anonnotice .siteNoticeSmallUser{display:none !important;}\n#centralNotice.usernotice .siteNoticeSmallAnon{display:none !important;}\n\x3c/style\x3e");

wgNotice=pickTemplate(["\x3cstyle type=\"text/css\"\x3e \n/* Styles for Notices */\n\n.notice-wrapper-strategy2, .notice-collapsed-wrapper-strategy2 {\n margin: 2px auto 0;\n width: 100%;\n padding: 0;\n font-family: \'Arial\',\'Helvetica\',\'Tahoma\',sans-serif;\n color: #333;\n background-color: #ddd;\n font-weight: 200;\n vertical-align:middle;\n}\n\n.notice-wrapper-strategy2 {\n border: 1px solid #bbb;\n background-color: #fcfcfc;\n text-align: left;\n}\n\n.notice-wrapper-strategy2 a {\n color: #006699;\n}\n\n.toggle-box-strategy2 {\n padding: 0;\n white-space: nowrap;\n}\n\ntd#table-cell-1 {\n margin: 0 auto;\n padding: 1px 0 3px 5px;\n width: 30px;\n}\n\ntd#table-cell-2 {\n margin: 0 auto;\n padding: 0 5px 0 0;\n font-size: 1.2em;\n}\n\ntd#table-cell-3 {\n text-align:right;\n font-size:.8em;\n padding:0 5px 0 0;\n}\n\n.line-ht-fix {\n line-height: 1em;\n}\n\n#centralNotice.collapsed .siteNoticeUser {\n display:none;\n}\n\ndiv.notice-links-strategy2 {\n text-align:right;\n}\n\x3c/style\x3e\n\n\x3ctable class=\"siteNoticeUser notice-wrapper-strategy2\"\x3e\n \x3ctr\x3e\n  \x3ctd id=\"table-cell-1\"\x3e\n   \x3cspan id=\"image-strategy\"\x3e\n    \x3ca title=\"Wikimedia Strategy\" href=\"http://strategy.wikimedia.org\"\x3e\x3cimg alt=\"Wikimedia Community logo\" src=\"http://upload.wikimedia.org/wikipedia/commons/thumb/7/75/Wikimedia_Community_Logo.svg/30px-Wikimedia_Community_Logo.svg.png\" style=\"border: none; float: left; height:30px;  width:30px; margin-right: .4em; vertical-align: middle;\" /\x3e\x3c/a\x3e\n   \x3c/span\x3e\n  \x3c/td\x3e\n  \x3ctd id=\"table-cell-2\"\x3e\n   \x3cspan\x3e\n    Aidez à construire le futur de Wikipédia et de ses projets frères ! \x3cBR\x3e \x3ca href=\"http://volunteer.wikimedia.org\"\x3eLisez l\'appel\x3c/a\x3e de Michael Snow et Jimmy Wales.\n   \x3c/span\x3e\n  \x3c/td\x3e\n  \x3ctd id=\"table-cell-3\" class=\"line-ht-fix\"\x3e\n   \x3cspan class=\"toggle-box-strategy2\"\x3e[\x3ca href=\"#\" onclick=\"toggleNotice();return\n   false\"\x3eRéduire\x3c/a\x3e]\x3c/span\x3e [\x3ca href=\"http://strategy.wikimedia.org/wiki/Strategic_Planning:Translation\"\x3eAidez-nous à traduire cet appel !\x3c/a\x3e]\n   \x3c/span\x3e\n  \x3c/td\x3e\n \x3c/tr\x3e\n\x3c/table\x3e"],[100]);
if (wgNotice != '')
wgNotice='<div id="centralNotice" class="' + (wgNoticeToggleState ? 'expanded' : 'collapsed') + ' ' + (wgUserName ? 'usernotice' : 'anonnotice' ) + '">' + wgNotice+'</div>';
