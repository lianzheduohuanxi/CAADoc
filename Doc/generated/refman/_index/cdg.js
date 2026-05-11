function getRelPath(iLevel,ideep) {	
 	var curDeep; 
 	if(ideep==0){ 
 	  curDeep = "../"; 
 	}else { 
 	  curDeep =  "../../"; 
 	} 
 	if (iLevel == "IPublic") {	
 		return curDeep + "IPublic/_index/"; 
 	} else if (iLevel == "IProtected") {	
 		return  curDeep + "IProtected/_index/"; 
 	} else if (iLevel == "IPrivate") {	
 		return  curDeep + "IPrivate/_index/"; 
 	} else return ""; 
 } 
 function getClassNameFromLevel(iLevel) { 
 	if (iLevel == "IPublic") { 
 		return "ongletPub"; 
 	} else if (iLevel == "IProtected") {  
 		return "ongletPro"; 
 	} else if (iLevel == "IPrivate") {	 
 		return "ongletPriv"; 
 	} else return ""; 
 } 
 function loadJs(id, ipath, iname) { 
 	var srcPath = ipath + iname; 
 	var curElem = document.getElementById(id); 
 	if (curElem){ 
 	 var parentElem = curElem.parentNode; 
 	 parentElem.removeChild(curElem); 
 	 var newScript = document.createElement("script"); 
 	 newScript.src = srcPath; 
 	 newScript.type = "text/javascript"; 
 	 newScript.id = id;	 
 	 parentElem.appendChild(newScript); 
 	} 
 } 
 function initDataFromLevel(iLevel,ideep) {	 
 	var curRelPath = getRelPath(iLevel,ideep); 
 	loadJs("jsLinkjs", curRelPath, "../_index/jslink.js"); 
 	var pathTmp = curRelPath + "../" + getCurrentFw(); 
 	loadJs("jsFwLinkjs", pathTmp, "/jsFwLink.js"); 
 	loadJs("jsTreejs", curRelPath, "../_index/jsTree.js"); 
 } 
 function appendNPOnglet(id,curObj, curType, npVal, classNameCur) { 
 	var elem = document.getElementById(id); 
 	if (elem ) { 
 		elem.className = classNameCur; 
 		elem.id = id; 
 		elem.rel = "#"; 
 		var test = locateObject(curObj, curType, npVal); 
 		if (test == 1) {		 
 			elem.href = "javascript:" +  "openLinkNP('" + curObj + "','" + curType + "','" + npVal + "')" ;		 
 			//var att = document.createAttribute("onclick"); 
 			//att.nodeValue = "openLinkNP('" + curObj + "','" + curType + "','" + npVal + "');return false"; 
 			//elem.setAttributeNode(att);			 
 		} else { 
 			elem.removeAttribute("href"); 
 			elem.removeAttribute("onclick");  
 		} 
 	} 
 } 
 function writeIndex(ILevel,ideep) {	 
 	var curLevel = ILevel;   
 	initDataFromLevel(ILevel,ideep); 
 	var classNameCur = getClassNameFromLevel(ILevel); 
 	var curRelPath = getRelPath(curLevel,ideep); 
 	var tabs = document.getElementsByName("multiview"); 
 	if (tabs) { 
 		var tmpValue; 
 		for (var i = 0; i < tabs.length; i++) { 
 			tmpValue = tabs[i].rel;		 
 			tabs[i].href = curRelPath + tmpValue; 
 			tabs[i].className = classNameCur;	 
 		} 
 		if(window.getCurrentObjectName && window.getCurrentType){var curObj = getCurrentObjectName(); 
 			var curType = getCurrentType(); 
 			appendNPOnglet("multiviewP", curObj, curType, "0", classNameCur); 
 			appendNPOnglet("multiviewN", curObj, curType, "1", classNameCur); }
 	}	 
 } 
 function initData(ideep) {	 
 	var iLevel = getCurrentLevel(); 
 	writeIndex(iLevel,ideep); 
 	var parent = document.getElementById("menuViewPPP");  
 	if (parent) { 
 		var elem=null; 
 		if (PubDirExist == false) { 
 			elem = document.getElementById("PublicView"); 
 			parent.removeChild(elem); 
 		} 
 		if (ProDirExist == false) { 
 			elem = document.getElementById("ProtectedView"); 
 			parent.removeChild(elem); 
 		} 
 		if (PrivDirExist == false) { 
 			elem = document.getElementById("PrivateView"); 
 			parent.removeChild(elem); 
 		} 
 	} 
 } 
 