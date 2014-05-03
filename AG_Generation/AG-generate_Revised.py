#-*- coding:utf-8 -*-
import xml.etree.ElementTree as ET
import networkx as nx
import json
import HostPrilvage as Priv

#读取xml文件
def xmlpython(xml1,n):
    xml2=open(xml1).read()
    G=create_graph(xml2,n)  
    return G

def create_graph(xml1,n):
    G=nx.DiGraph()      #创建有向图      
    H=nx.DiGraph()      #创建存储父节点的图
    root=ET.fromstring(xml1)    #获取xml的根节点
    G=first_node(G,root)    #存储第一个点
    i=1
    ip1=G.node[1]['ip']
    com1=G.node[1]['com']
    G=post_node(G,H,i,root,n)
    return G

def post_node(G,H,i,root,n):
    d=i
    ip2=G.node[i]['ip']
    com2=G.node[i]['com']
    H.add_node(i,ip=ip2,com=com2)       #将自身当做父节点存入H图中
    for vid1 in root.findall('./vid'):  #遍历vid元素，查找ip
        lenH=H.nodes()
        if len(lenH)==n:        #判断父节点个数是否超过限定    
            break
        ip1=vid1.get('ip')      #获取vid的ip
        for attack1 in vid1.findall('./attack'):    #遍历attack元素，查找攻击
            b=0
            c=0
            pr1=attack1.find('./pr').text
            post1=attack1.find('./post').text

            for x in H.nodes():     #如果后果点在父节点中，就返回
                if H.node[x]['ip']==ip1 and post1 in H.node[x]['com']:
                    b=1
                    break
            if b==1:
                continue

            for x in G.nodes():     #如果后果点在G图中，就直接建立边
                if G.node[x]['ip']==ip1 and post1 in G.node[x]['com']:
                    G.add_edge(d,x,pr=pr1)
                    c=1
                    break

            if c==1:
                continue
            else:
            
                if post1=='root':
                    post2=Priv.root_priv
                elif post1=='user':
                    post2=Priv.user_priv
                elif post1=='login':
                    post2=Priv.login_priv
                elif post1=='access':
                    post2=Priv.access_priv
            
                G.add_node(i+1,ip=ip1,com=post2)
                G.add_edge(d,i+1,pr=pr1)
                i=i+1
                
                G=post_node(G,H,i,root,n)
                                    
    H.remove_node(d)
    return G

#输入第一个攻击点
def first_node(G1,root):
    ip1='192.168.1.101'
    pr1='0.5'
    post1=Priv.root_priv

    #判断权限包含关系
    '''
    if post1=='root':
        post1=['root','user','login','access']
    if post1=='user':
        post1=['user','login','access']
    if post1=='login':
        post1=['login','access']
    if post1=='access':
        post1=['access']
    '''
    G1.add_node(1,ip=ip1,com=post1)
    return G1
    

if __name__ == '__main__':
    f=file("Network_link.json")
    net_link=json.load(f)
    
    ''' Load Json File of Netork topology & Test all of this is OK
	Test the json load of network topology is ok for all the 
	things in this area

    print net_link
    print "network_keys"
    print net_link.keys()
    print "network_link 0f 192.168.1.1"
    print net_link["192.168.1.101"]
    test_list=net_link["192.168.1.101"]
    compare_string=test_list[1].encode("utf-8")
    if(test_list[1]=='192.168.1.103'):
	print ""	
	print "YES"
	print ""
    else:
	print "ERROR ERROR ERROR"
	print test_list[1]

    '''	
    n=raw_input('输入单一路径的最大节点数：')
    G=xmlpython('exploit.xml',n)
    
    #way1=raw_input('输入生成G.node的json文件的路径，不包括文件名：')
    f=open('G.node.json','w')
    f.write(json.dumps(G.node,sort_keys=True,indent=4))
    f.close()
    #way2=raw_input('输入生成G.edge的json文件的路径，不包括文件名：')
    f=open('G.edge.json','w')
    f.write(json.dumps(G.edge,sort_keys=True,indent=4))
    f.close()

    print "生成的 G.node:"
    print json.dumps(G.node,sort_keys=True,indent=4)

    print "生成的 G.edge:"
    print json.dumps(G.edge,sort_keys=True,indent=4)
    
