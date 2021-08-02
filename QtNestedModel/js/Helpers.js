.pragma library

function isObject(o){
    return (
                !(Array.isArray(o))
            &&  !(typeof o === 'function')
            &&  (typeof o === 'object' || o instanceof Object)
                )
}

function creationEditeur(items,o){
    if(typeof(o) === "string" || o instanceof String){
        items.insert()
    }
    else{
        for( var key in o){
            console.info("key:" + key)
            var el = o[key]
            if(isObject(el)){
                exposerObjet(el)
            }else if(Array.isArray(el)){
                for(var karr in el){
                    exposerObjet(el[karr])
                }
            }else{
                console.info(el)
            }
        }
    }

}

function exposerObjet(o){

    if(typeof(o) === "string" || o instanceof String){
        console.info(o)
    }
    else{
        for( var key in o){
            console.info("key:" + key)
            var el = o[key]
            if(isObject(el)){
                exposerObjet(el)
            }else if(Array.isArray(el)){
                for(var karr in el){
                    exposerObjet(el[karr])
                }
            }else{
                console.info(el)
            }
        }
    }
}

function vide(){return;}

//utilisation
// selected = selected.filter(Hlp.unicite)
function unicite(self, index,value){
    return self.indexOf(value)=== index
}


function removeElement(list,el){
    list.splice(list.indexOf(el),1)
}

function changeElement(list,index,field,value){
    var edit = list[index]
    edit[field]=value
}

