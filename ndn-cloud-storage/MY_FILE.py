class myFile:
    def __init__(self,name,id,mtype,time,status,parent):
        self._name = name
        self._id = id
        self._type = mtype
        self._time = time
        self._status = status
        self._parent = parent

    def get_name(self):
        return self._name
    def set_name(self,name):
        self._name = name
    def get_id(self):
        return self._id
    def set_id(self,id):
        self._id = id
    def get_type(self):
        return self._type
    def set_user(self,mtype):
        self._type = mtype
    def get_time(self):
        return self._time
    def set_time(self,time):
        self._time = time
    def get_status(self):
        return self._status
    def set_status(self,status):
        self._status = status
    def get_parent(self):
        return self._parent
    def set_parent(self,parent):
        self._parent = parent
    def __eq__(self,other):
        return self._id == other._id and self._name == other._name
    def __gt__(self,other):
        return self._time > other._time 
    def __str__(self):
        return self._type + "     " + self._id + "     " + self._name  + "     " + str(self._time) + "     " + self._status +"     "+self._parent+ '\n'; 