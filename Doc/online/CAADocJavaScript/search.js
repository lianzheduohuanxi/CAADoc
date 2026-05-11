var index_file_data = "";
var ModuleNumber = [];
var DocIndex = [];
var PartNumber = [];
var nb_doc = 0;
var k1=0;
var mod_name="";
var mod_name_list=[];
var longVal = new Long(1, 1);
var current_module;
var ResultSet = [];
var Resultsetdata = [];
var ResultSet_URL = [];
var filter;
var result_final = [];
var result_url_final = [];
var old_word = "";
var old_filter = "";
var index_file = "";
var old_product_search_list = [];
var installedMod = [];

// ----------------------------------------------------------------------------------------
function isfound(modnum, index, partnum) {
    var flag = false;
    for (i = 0 ; i < nb_doc ; i++) {
        if ((ModuleNumber[i] == modnum) && (DocIndex[i] == index) && (PartNumber[i] == partnum)) {
            flag = true;
            break;
        }
    }
    if (flag) return 0;
    return -1;
}

// ----------------------------------------------------------------------------------------
function ajoute(modnum, index, partnum, rs, rsurl) {
    ModuleNumber[nb_doc] = modnum;
    DocIndex[nb_doc] = index;
    PartNumber[nb_doc] = partnum;
    mod_name_list[k1] = mod_name;
    var doc_no = rs.length;
    rs[doc_no] = partTitlesForModuleS[modnum];
    rs[doc_no] = rs[doc_no] + "-" + current_module.TitleList[index];
    rsurl[doc_no] = mod_name + "/" + current_module.FileList[index];
    nb_doc++;
    k1++;
}

// ----------------------------------------------------------------------------------------
function add_result(modno, word, Bits, rs, rsurl) {
    var DocIndex = 0;
    for (BitIndex = 0; BitIndex < Bits.length; BitIndex++) {
        var CurrentBits = Bits[BitIndex];
        for (var Shift = 0; Shift < 32; Shift++) {
            if ((CurrentBits & (longVal.low)) != 0) {
                var PartNumber = 0;
                if (DocIndex >= 1) {
                    PartNumber = 0;
                }
                var trouve = isfound(modno, DocIndex, PartNumber);
                if (trouve != 0) {
                    ajoute(modno, DocIndex, PartNumber, rs, rsurl);
                }
            }
            CurrentBits >>>= 1;
            DocIndex++;
        }
    }
    return 0;
}

// ----------------------------------------------------------------------------------------
function Intersection(result_temp, result_url_temp) {
    var x = 0;
    var temp = [], temp_url = [];
    for (i2 = 0 ; i2 < result_final.length ; i2++) {
        for (i = 0 ; i < result_temp.length ; i++) {
            if (result_final[i2] == result_temp[i] && result_url_final[i2] == result_url_temp[i]) {
                temp[x] = result_temp[i];
                temp_url[x] = result_url_temp[i];
                x++;
                break;
            }
        }
    }
    result_final = [];
    result_url_final = [];
    result_final.push.apply(result_final, temp);
    result_url_final.push.apply(result_url_final, temp_url);
}

// ----------------------------------------------------------------------------------------
function SearchString(word, modno, match) {
    var x = 10;
    var Bits = [];
    current_module = index_file_data[Object.keys(index_file_data)[modno]];
    mod_name = Object.keys(index_file_data)[modno];
	var Modfound = false;
	
	//check if module is installed
	for (i = 0; i < installedMod.length; i++) {
		if((installedMod[i].toLowerCase()) == (mod_name.toLowerCase())) {
			Modfound = true;
			break;
		}
    }
	
	if(Modfound == true) {
		var wordlist = current_module.WordList;
		var result_temp = [];
		var result_url_temp = [];
		result_final = [];
		result_url_final = [];
		for (z = 0; z < word.length; z++) {
			result_url_temp = [];
			result_temp = [];
			if (filter != "OR") {
				nb_doc = 0;
				ModuleNumber = [], DocIndex = [], PartNumber = [];

			}
			for (var key in wordlist) {
				if (wordlist.hasOwnProperty(key)) {
					if (match == false && key.toLowerCase().indexOf(word[z].toLowerCase()) !== -1) {
						Bits = wordlist[key];
						add_result(modno, word, Bits, result_temp, result_url_temp);
					}
					else {
						if (key.toLowerCase() == (word[z].toLowerCase())) {
							Bits = wordlist[key];
							add_result(modno, word, Bits, result_temp, result_url_temp);
						}
					}
				}
			}
			if (filter == "AND" || filter == "Exact Phrase") {
				if (z == 0) {
					result_final.push.apply(result_final, result_temp);
					result_url_final.push.apply(result_url_final, result_url_temp);
				}
				else {
					if (result_temp.length != 0)
						Intersection(result_temp, result_url_temp);
					else {
						result_final = [];
						result_url_final = [];
						break;
					}
				}
			}
			else {
				ResultSet.push.apply(ResultSet, result_temp);
				ResultSet_URL.push.apply(ResultSet_URL, result_url_temp);
			}
		}
		if (result_final.length != 0) {
			ResultSet.push.apply(ResultSet, result_final);
			ResultSet_URL.push.apply(ResultSet_URL, result_url_final);
		}
	}
}

// ----------------------------------------------------------------------------------------
function process_exact_phrases(input_string) {
    input_string = input_string.join("");
    var url = window.location.href;
    var ResultSet_final = [];
    var ResultSet_URL_final = [];
    var z = 0;
    for (k = 0; k < ResultSet_URL.length; k++) {
        url = url.substring(0, url.indexOf("online"));
        url = url + "online/" + ResultSet_URL[k];
        var htmstr = loadFile_mod(url, "txt");
        htmstr = htmstr.replace(/ /g, '');
        var index = (htmstr.toLowerCase()).indexOf(input_string.toLowerCase());
        if (index > 0) {
            ResultSet_final[z] = ResultSet[k];
            ResultSet_URL_final[z] = ResultSet_URL[k];
            z++;
        }
    }
    ResultSet = [];
    ResultSet_URL = [];
    ResultSet.push.apply(ResultSet, ResultSet_final);
    ResultSet_URL.push.apply(ResultSet_URL, ResultSet_URL_final);
    ResultSet_URL_final = [];
    ResultSet_final = [];
}

// ----------------------------------------------------------------------------------------
function Search(mybrand, ModulesList, product_search_list) {
	installedMod = ModulesList;
    var index_file_name = mybrand + "_index.json";
    var iString = $('#usersearch').val();
    if (iString == "")
        return;
    filter = $("#select_class :selected").text();
    var match = $('#match').is(":checked");
    var input_string = [];
    input_string = iString.split(" ");

    var prod_count = 0;

    //if(old_word.toLowerCase() == iString.toLowerCase() && old_filter == "AND" && filter == "Exact Phrase")
    //process_exact_phrases(input_string);

    ResultSet = [];
    ResultSet_URL = [];

    if (index_file == "")
        index_file = loadFile_mod(index_file_name, "txt");

    if (index_file_data == "")
        index_file_data = JSON.parse(index_file);
    var flag_prod = false;

    if (product_search_list != undefined && product_search_list != null && product_search_list.length != 0) {
        for (j = 0; j < indexModuleToCheck; j++) {
            flag_prod = false;
            for (q = 0; q < product_search_list.length; q++) {
                if (product_search_list[q].text == partTitlesForModuleS[j]) {
                    flag_prod = true;
                    break;
                }
            }
            if (flag_prod)
                Bits = SearchString(input_string, j, match);
        }
    }
    else {
        for (j = 0; j < indexModuleToCheck; j++) {
            Bits = SearchString(input_string, j, match);
        }
    }

    if (filter == "Exact Phrase") {
        process_exact_phrases(input_string);
    }

    old_word = iString;
    old_filter = filter;
    if (product_search_list != null && product_search_list != undefined && product_search_list.length != 0)
        old_product_search_list.push.apply(old_product_search_list, product_search_list);
    ModuleNumber = [];
    PartNumber = [];
    DocIndex = [];
    nb_doc = 0;
}
