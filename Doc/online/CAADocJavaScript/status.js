var indexModuleToCheck = 0;
var partTitlesForModuleS = [];
var bookchoice = [];
var bookchoicesol = [];
var ModToCheck = [];

// ----------------------------------------------------------------------------------------
String.prototype.compareTo = function (anotherString, lo, hi0) {
    var len1 = this.length;
    var len2 = anotherString.length;
    var n = Math.min(len1, len2); //If the lengths will always be the same skip n to be assigned to len1 only, get rid of len2
    var v1 = this;
    var v2 = new String(anotherString);
    // You could instead set these vars i and j to passed in offsets if you want to start sorting from, in which case else case will be possible, or only the first i == j if statement will always be run
    var i = 0;
    var j = 0;

    if (i == j) {
        var k = i;
        var lim = n + i;
        while (k < lim) {
            var c1 = v1[k];
            var c2 = v2[k];
            if (c1 != c2) {
                var returnVal = c1.charCodeAt(0) - c2.charCodeAt(0);
                if (returnVal > 0)
                    return 1;
                else
                    return -1
                return 0;
            }
            k++;
        }
    } else {
        while (n-- != 0) {
            var c1 = v1[i++];
            var c2 = v2[j++];
            if (c1 != c2) {
                var returnVal = c1.charCodeAt(0) - c2.charCodeAt(0);
                if (returnVal > 0)
                    return 1;
                else
                    return -1
                return 0;
            }
        }
    }
    return len1 - len2;
    //return 0; //if lengths are always the same, comment the above line, uncomment this line
}

// ----------------------------------------------------------------------------------------
function swap(array, i, j) {
    var temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

// ----------------------------------------------------------------------------------------
function QuickSort(a, modu, lo0, hi0) {
    var lo = lo0;
    var hi = hi0;
    var mid = null;

    if (hi0 > lo0) {

        /*
         * Arbitrarily establishing partition element as the midpoint of the
         * array.
         */
        mid = a[Math.round((lo0 + hi0) / 2)];

        // loop through the array until indices cross
        while (lo <= hi) {
            /*
             * find the first element that is greater than or equal to the
             * partition element starting from the left Index.
             */
            while ((lo < hi0) && (a[lo].compareTo(mid, lo, hi0) < 0))
                ++lo;

            /*
             * find an element that is smaller than or equal to the
             * partition element starting from the right Index.
             */
            while ((hi > lo0) && (a[hi].compareTo(mid, lo, hi0) > 0))
                --hi;

            // if the indexes have not crossed, swap
            if (lo <= hi) {
                swap(a, lo, hi);
                swap(modu, lo, hi);
                ++lo;
                --hi;
            }
        }

        /*
         * If the right index has not reached the left side of array must
         * now sort the left partition.
         */
        if (lo0 < hi)
            QuickSort(a, modu, lo0, hi);

        /*
         * If the left index has not reached the right side of array must
         * now sort the right partition.
         */
        if (lo < hi0)
            QuickSort(a, modu, lo, hi0);
    }
}

// ----------------------------------------------------------------------------------------
function charge_index_status(mybrand) {
    // 1.Manage Product index

    var install_list = mybrand + "_INDEXFile.DSidx";
    var product_list = loadFile_mod(install_list, "txt");
    var module = product_list.split('\n');

    var bookchoice_index = 0;
    for (var i = 0; i < (module.length) - 1; i++) {
        ModToCheck[indexModuleToCheck] = module[i];
        i++;
        var titleModule = module[i];
        partTitlesForModuleS[indexModuleToCheck] = titleModule;
        if (bookchoice.indexOf(titleModule) == -1) {
            bookchoice[bookchoice_index] = titleModule;
            bookchoice_index++;
        }
        indexModuleToCheck++;
    }

    indexModuleToCheck--;
    bookchoice.sort();
    QuickSort(partTitlesForModuleS, ModToCheck, 0, indexModuleToCheck);

    // 2.Manage Solution index
    var ModToCheckSolution = [];
    var indexModuleToCheckSolution = 0;
    var partTitlesForModuleSSolution = [];

    var install_list_next = mybrand + "_INDEXFile.SOLidx";
    var product_list_next = loadFile_mod(install_list_next, "txt");
    var module_next = product_list_next.split('\n');

    var bookchoicesol_index = 0;
    for (var i = 0; i < (module.length) - 1; i++) {
        ModToCheckSolution[indexModuleToCheckSolution] = module_next[i];
        i++;
        var titleModule = module_next[i];
        partTitlesForModuleSSolution[indexModuleToCheckSolution] = titleModule;
        if (bookchoicesol.indexOf(titleModule) == -1) {
            bookchoicesol[bookchoicesol_index] = titleModule;
            bookchoicesol_index++;
        }
        indexModuleToCheckSolution++;
    }

    indexModuleToCheckSolution--;
    QuickSort(partTitlesForModuleSSolution, ModToCheckSolution, 0, indexModuleToCheckSolution);
    bookchoicesol.sort();
}
